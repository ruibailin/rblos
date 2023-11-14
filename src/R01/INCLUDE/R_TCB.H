#ifndef _r_tcb_h
#define _r_tcb_h

#define MAX_TCB_NUM   1024

typedef struct{
  TAG   tag;
  CSN   csn;
  WORD  len;
  WORD  rst;
  BYTE  tno;
  BYTE  pno;
}TCB;

/*------------------------------------*/
#define   TCB_QUEUE_NUM      12
#define   TimerIdleQueue     MAX_TCB_NUM+0
#define   TimerL50msQueue    MAX_TCB_NUM+1
#define   Timer50msQueue     MAX_TCB_NUM+2
#define   Timer100msQueue    MAX_TCB_NUM+3
#define   Timer500msQueue    MAX_TCB_NUM+4
#define   Timer1sQueue       MAX_TCB_NUM+5
#define   Timer5sQueue       MAX_TCB_NUM+6
#define   Timer10sQueue      MAX_TCB_NUM+7
#define   Timer50sQueue      MAX_TCB_NUM+8
#define   Timer100sQueue     MAX_TCB_NUM+9
#define   TimerBusyQueue     MAX_TCB_NUM+10
/*------------------------------------*/
extern  TCB   far *TCBPool;
extern  void  far ini_tcb_queue(void);
extern  void  far run_tcb_queue(void);

extern  WORD  far get_tcb_arrived(void);
extern  void  far free_tcb_arrived(WORD item);
/*------------------------------------*/
#endif

/*End Of tcb.h*/

