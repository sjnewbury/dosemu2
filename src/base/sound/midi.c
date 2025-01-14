/*
 *  Copyright (C) 2006 Stas Sergeev <stsp@users.sourceforge.net>
 *
 * The below copyright strings have to be distributed unchanged together
 * with this file. This prefix can not be modified or separated.
 */

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <string.h>
#include "emu.h"
#include "ringbuf.h"
#include "timers.h"
#include "utilities.h"
#include "sound/sound.h"
#include "sound.h"
#include "sound/midi.h"

#define MAX_OUT_PLUGINS 15
/* support only 1 input plugin for now to avoid the concurrent writes */
#define MAX_IN_PLUGINS 1
static struct pcm_holder out[ST_MAX][MAX_OUT_PLUGINS];
static struct pcm_holder in[MAX_IN_PLUGINS];
#define OUT_PLUGIN(i, j) ((const struct midi_out_plugin *)out[i][j].plugin)
#define IN_PLUGIN(i) ((const struct midi_in_plugin *)in[i].plugin)
static int out_registered[ST_MAX], in_registered;
static int out_enabled[ST_MAX];
static struct rng_s midi_in;
#define MAX_DL_HANDLES 10
static void *dl_handles[MAX_DL_HANDLES];
static int num_dl_handles;
static enum SynthType synth_type;

void midi_write(unsigned char val, enum SynthType type)
{
    int i;
    enum SynthType stype = (type == ST_ANY ? synth_type : type);
    /* if no plugin of requested type, then try to use anything */
    if (!out_enabled[stype] && out_enabled[synth_type])
	stype = synth_type;
    for (i = 0; i < out_registered[stype]; i++)
	if (out[stype][i].opened)
	    OUT_PLUGIN(stype, i)->write(val);
    for (i = 0; i < out_registered[ST_ANY]; i++)
	if (out[ST_ANY][i].opened)
	    OUT_PLUGIN(ST_ANY, i)->write(val);
//  idle(0, 0, 0, "midi");
}

void midi_init(void)
{
    int i, j;
#ifdef USE_DL_PLUGINS
#define LOAD_PLUGIN(x) \
    dl_handles[num_dl_handles] = load_plugin(x); \
    if (dl_handles[num_dl_handles]) \
	num_dl_handles++
#ifdef USE_FLUIDSYNTH
    LOAD_PLUGIN("fluidsynth");
#endif
#ifdef USE_MUNT
    LOAD_PLUGIN("munt");
#endif
#ifdef USE_ALSA
    LOAD_PLUGIN("alsa");
#endif
#endif
    rng_init(&midi_in, 64, 1);
    for (i = 0; i < ST_MAX; i++) {
	pcm_init_plugins(out[i], out_registered[i]);
	for (j = 0; j < out_registered[i]; j++) {
	    if (out[i][j].opened)
		out_enabled[i]++;
	}
    }
    pcm_init_plugins(in, in_registered);

    if (!midi_set_synth_type_from_string(config.midi_synth))
	error("MIDI: unsupported synth mode %s\n", config.midi_synth);
}

void midi_done(void)
{
    int i;
    midi_stop();
    for (i = 0; i < ST_MAX; i++)
	pcm_deinit_plugins(out[i], out_registered[i]);
    pcm_deinit_plugins(in, in_registered);
    rng_destroy(&midi_in);
    for (i = 0; i < num_dl_handles; i++)
#if 0
	close_plugin(dl_handles[i]);
#else
	(void)dl_handles[i];
#endif
}

void midi_stop(void)
{
    int i, j;
    for (i = 0; i < ST_MAX; i++) {
	for (j = 0; j < out_registered[i]; j++)
	    if (OUT_PLUGIN(i, j)->stop && out[i][j].opened)
		OUT_PLUGIN(i, j)->stop(out[i][j].arg);
    }
    for (i = 0; i < in_registered; i++)
	if (IN_PLUGIN(i)->stop && in[i].opened)
	    IN_PLUGIN(i)->stop(in[i].arg);
}

void midi_timer(void)
{
    int i, j;
    for (i = 0; i < ST_MAX; i++) {
	for (j = 0; j < out_registered[i]; j++)
	    if (OUT_PLUGIN(i, j)->run && out[i][j].opened)
		OUT_PLUGIN(i, j)->run();
    }
}

void midi_put_data(unsigned char *buf, size_t size)
{
    rng_add(&midi_in, size, buf);

    run_sb();
}

int midi_get_data_byte(unsigned char *buf)
{
    if (!rng_count(&midi_in))
	return 0;
    return rng_get(&midi_in, buf);
}

int midi_register_output_plugin(const struct midi_out_plugin *plugin)
{
    int index, st = plugin->stype;
    if (out_registered[st] >= MAX_OUT_PLUGINS) {
	error("Cannot register midi plugin %s\n", plugin->name);
	return 0;
    }
    index = out_registered[st]++;
    out[st][index].plugin = plugin;
    out[st][index].opened = 0;
    return 1;
}

int midi_register_input_plugin(const struct midi_in_plugin *plugin)
{
    int index;
    if (in_registered >= MAX_IN_PLUGINS) {
	error("Cannot register midi plugin %s\n", plugin->name);
	return 0;
    }
    index = in_registered++;
    in[index].plugin = plugin;
    in[index].opened = 0;
    return 1;
}

int midi_set_synth_type(enum SynthType st)
{
    if (st == ST_ANY || st >= ST_MAX || !out_enabled[st])
	return 0;
    synth_type = st;
    return 1;
}

enum SynthType midi_get_synth_type(void)
{
    return synth_type;
}

int midi_set_synth_type_from_string(const char *stype)
{
    if (strcmp(stype, "gm") == 0)
	return midi_set_synth_type(ST_GM);
    if (strcmp(stype, "mt32") == 0)
	return midi_set_synth_type(ST_MT32);
    midi_set_synth_type(ST_GM);
    return 0;
}
