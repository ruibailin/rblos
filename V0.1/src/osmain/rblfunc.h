/* ZXJ10.H
   Copyright(c) 1993-1997. (ZTE)Shenzhen Zhongxing New Telecom Equip. Co. Ltd.
   Research Institute of Nanjing Zhongxing New Telecom.
   All rights reserved. */

#ifndef __rblos_h
#define __rblos_h
#include "rbltype.h"

extern VFAR   NEXT(WORD State);
extern VFAR   SELF(PID FAR *PidPtr);
extern WFAR   EVENT(void);
extern VFAR   SENDER(PID FAR *PidPtr);
extern WFAR   STATE(void);
extern WFAR   LENGTH(void);

extern WFAR   ASEND(WORD Event, BFAR *In, WORD InLen, PID *Receiver);
extern WFAR   MSEND(WORD Event, BFAR *In, WORD InLen, PID *Receiver);

extern WFAR   SET(WORD Count100ms, WORD TimerNo);
extern VFAR   KILL(WORD TimerNo);
#endif

