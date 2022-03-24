#ifndef _rblstart_h
#define _rblstart_h
#include "rbltype.h"
extern VFAR cli_int();
extern VFAR sti_int();
extern WFAR get_sp();
extern VFAR set_sp(WORD sp);
extern VFAR next_ret(WORD sp);
extern VFAR send_ret();
#endif
