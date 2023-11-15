#ifndef _r_pcb_h
#define _r_pcb_h
#include "rbltype.h"
#define MAX_PCB_NUM     32

typedef struct{
  TAG   tag;                          /*define  in r_tcb.h*/
  WORD  thisstate;
  WORD  laststate;
  WORD  thisevent;
  WORD  lastevent;
  WORD  timer[8];
  BFAR *input;
}PCB;

/*------------------------------------*/
#define   PCB_QUEUE_NUM      5
#define   ProIdleQueue    MAX_PCB_NUM+0
#define   Pro10msQueue    MAX_PCB_NUM+1
#define   Pro100msQueue   MAX_PCB_NUM+2
#define   Pro1000msQueue  MAX_PCB_NUM+3
#define   Pro0msQueue     MAX_PCB_NUM+4       /*Accurate 10ms*/


/*------------------------------------*/
extern  PCB  FAR *PCBPool;
extern  VFAR ini_pcb_queue(void);
extern  VFAR run_pcb_queue(WORD queue);
extern  VFAR run_pcb_msg(void);

/*------------------------------------*/
#endif
/*End of r_pcb.h*/

