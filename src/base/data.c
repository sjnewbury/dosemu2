#define EXTERN
#define INIT(x...)		= x

#include <termios.h>
#include <sys/types.h>
#include "config.h"
#include "emu.h"
#include "mapping.h"
#include "xms.h"
#include "disks.h"
#include "timers.h"
#include "int.h"
#include "hma.h"
#include "termio.h"
#include "machcompat.h"
#include "vc.h"
#include "video.h"
#include "mouse.h"
#include "bios.h"
#include "dpmi.h"
#include "pic.h"
#include "disks.h"
#include "mhpdbg.h"
#include "cmos.h"
#include "priv.h"
#include "dma.h"
#include "sound.h"
#include "serial.h"
#include "dosemu_debug.h"
#include "keyb_server.h"
#include "keyb_clients.h"
