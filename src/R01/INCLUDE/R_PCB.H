#ifndef _r_pcb_h
#define _r_pcb_h
#define MAX_PCB_NUM     64

typedef struct{
  TAG   tag;                          /*define  in r_tcb.h*/
  WORD  thisstate;
  WORD  laststate;
  WORD  thisevent;
  WORD  lastevent;
  WORD  timer[8];
  BYTE  far *input;
}PCB;

/*------------------------------------*/
#define   PCB_QUEUE_NUM      6
#define   ProIdleQueue    MAX_PCB_NUM+0
#define   Pro10msQueue    MAX_PCB_NUM+1
#define   Pro100msQueue   MAX_PCB_NUM+2
#define   Pro1000msQueue  MAX_PCB_NUM+3
#define   Pro0msQueue     MAX_PCB_NUM+4       /*Accurate 10ms*/
#define   Pro400msQueue   MAX_PCB_NUM+5       /*Used for Init RING Queue*/

/*------------------------------------*/
extern  PCB   far *PCBPool;
extern  void  far ini_pcb_queue(void);
extern  void  far run_pcb_queue(WORD queue);
extern  void  far run_pcb_msg(void);
extern  void  far run_pcb_tcb(void);
/*------------------------------------*/
#endif
/*End of r_pcb.h*/

