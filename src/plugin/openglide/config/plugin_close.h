/* 
 * (C) Copyright 1992, ..., 2005 the "DOSEMU-Development-Team".
 *
 * for details see file COPYING in the DOSEMU distribution
 */

/*
 * This is file plugin_close.h for use within the src/plugin/<name>/
 *
 * It should contain a valid call to the init function of the plug-in such as
 *
 *       my_plugin_close();
 * 
 * This routine should do _nothing_, if its counterpart my_plugin_init()
 * did decide to disable the plugin.
 */

openglide_plugin_close();
