/* ZXJ10.H
   Copyright(c) 1993-1997. (ZTE)Shenzhen Zhongxing New Telecom Equip. Co. Ltd.
   Research Institute of Nanjing Zhongxing New Telecom.
   All rights reserved. */

#ifndef __ZXFUNC_H
#define __ZXFUNC_H

extern WORD16 far   ASEND(WORD16 Event, BYTE far *In, WORD16 InLen, PID Receiver);
extern WORD16 far   MSEND(WORD16 Event, BYTE far *In, WORD16 InLen, PID Receiver);
extern void   far   NEXT_STATE(WORD16 State);
extern void   far   SELF_PID(PID far *PidPtr);
extern WORD16 far   EVENT(void);
extern void   far   SENDER(PID far *PidPtr);
extern WORD16 far   STATE(void);
extern WORD16 far   LENGTH(void);

extern WORD16 far   SET_TIMER(WORD16 Count100ms, BYTE TimerNo);
extern WORD16 far   EXTRA_SET_TIMER(WORD16 Count100ms, BYTE TimerNo, CSN Extra);
extern void   far   KILL_TIMER(BYTE TimerNo);
extern void   far   EXTRA_KILL_TIMER(WORD16 tid);
extern void   far   CREATE(WORD pno,BYTE tno,void far *entry);

extern BYTE   far   *alloc_ram(WORD16 len);
extern BYTE   far   *alloc_rom(WORD16 len);
extern long   far   get_sys_tick(void);
extern long   far   get_cpu_rate(void);
extern void   far   clear_watch_dog(void);
extern WORD   far   GetCS(void);          /*Defined In R00*/
extern void   far   *GetCSIP(void);
extern WORD   far   GetSSSP(void);
#endif

