#include "rbltype.h"
#include "r_mem.h"
#include "r_msg.h"
#include "r_pcb.h"
#include "r_tcb.h"
#include "r_pat.h"

PCB FAR *PCBPool;
/*------------------------------------*/
/*Get Last TAG After A TAG*/
#define  GetLastTAG(item)  PCBPool[(item)].tag.last
/*------------------------------------*/
/*Get Next TAG After A TAG*/
#define  GetNextTAG(item)  PCBPool[(item)].tag.next
/*------------------------------------*/
/*Macro Judge whether a TAG is in a queue*/
#define  GetFirstTAG(item)  PCBPool[(item)].tag.root
/*------------------------------------*/
/*Browse a TAG In Queue */
static  void  BrowseTAG(WORD item);
void  BrowseTAG(WORD item)
{
  WORD next;
  next=PCBPool[item].tag.next;
  for(;;)
  {
    if(next == item) break;
    next=PCBPool[next].tag.next;
  }
}
/*------------------------------------*/
/*Put a TAG after one TAG*/
static  void  AppendTAG(WORD last,WORD item);
static  void  AppendTAG(WORD last,WORD item)
{
  WORD  next,root;
  TAG   FAR *lastptr;
  TAG   FAR *itemptr;
  TAG   FAR *nextptr;

  lastptr =(TAG FAR*)&(PCBPool[last].tag);
  root=lastptr->root;
  next=lastptr->next;
  lastptr->next=item;

  itemptr =(TAG FAR*)&(PCBPool[item].tag);
  itemptr->next=next;
  itemptr->last=last;
  itemptr->root=root;

  nextptr =(TAG FAR*)&(PCBPool[next].tag);
  nextptr->last=item;
}
/*------------------------------------*/
/*Put a TAG Befor one TAG*/
static  void  BeforeTAG(WORD next,WORD item);
static  void  BeforeTAG(WORD next,WORD item)
{
  WORD  last,root;
  TAG   FAR *nextptr;
  TAG   FAR *itemptr;
  TAG   FAR *lastptr;

  nextptr =(TAG FAR*)&(PCBPool[next].tag);
  root=nextptr->root;
  last=nextptr->last;
  nextptr->last=item;

  itemptr =(TAG FAR*)&(PCBPool[item].tag);
  itemptr->next=next;
  itemptr->last=last;
  itemptr->root=root;

  lastptr =(TAG FAR*)&(PCBPool[last].tag);
  lastptr->next=item;
}
/*------------------------------------*/
/*Delete a TAG From Queue */
static  void  DeleteTAG(WORD item);
static  void  DeleteTAG(WORD item)
{
  WORD last,next;
  TAG   FAR *itemptr;
  TAG   FAR *lastptr;
  TAG   FAR *nextptr;

  itemptr =(TAG FAR*)&(PCBPool[item].tag);
  last=itemptr->last;
  itemptr->last=item;
  next=itemptr->next;
  itemptr->next=item;
  itemptr->root=item;

  lastptr =(TAG FAR*)&(PCBPool[last].tag);
  lastptr->next=next;

  nextptr =(TAG FAR*)&(PCBPool[next].tag);
  nextptr->last=last;
}
/*------------------------------------*/
/*Make a TAG Is a Root In Queue */
static  void  QueueTAG(WORD item);
static  void  QueueTAG(WORD item)
{
  TAG   FAR *itemptr;

  itemptr =(TAG FAR*)&(PCBPool[item].tag);
  itemptr->next=item;
  itemptr->last=item;
  itemptr->root=item;
}
/*===========================================================================*/
WORD SysCurPno=0;

/*------------------------------------*/
void  ini_pcb_queue(void);
void  ini_pcb_queue()
{
  WORD  ii,jj;
  WORD  tno;

  ini_self_msg();
  ini_tcb_queue();

  ii=(MAX_PCB_NUM+PCB_QUEUE_NUM)*sizeof(PCB);
  PCBPool=(PCB FAR *)alloc_ram(ii);

  for(ii=0;ii<PCB_QUEUE_NUM;ii++)
  QueueTAG(MAX_PCB_NUM+ii);

  for(ii=0;ii<MAX_PCB_NUM;ii++)
  {
    for(jj=0;jj<8;jj++)
    PCBPool[ii].timer[jj]=0xffff;
    tno=get_pat_tno(ii);
    if(tno>=PCB_QUEUE_NUM) continue;
    BeforeTAG(ProIdleQueue+tno,ii);
  }
}
/*------------------------------------*/
void  run_pcb_queue(WORD queue);
void  run_pcb_queue(WORD queue)
{
  WORD  next;
  long  tick;
  WORD	BufCurPno;
  BufCurPno=SysCurPno;

  tick=0;
  next=GetNextTAG(queue);
  for(;;)
  {
    if(next==queue) break;            /*No More Timer Process To execute*/
    SysCurPno=next;

    PCBPool[SysCurPno].thisevent=0;
    EXEPROC(SysCurPno,(BFAR *)&tick);
    next=GetNextTAG(next);
  }

  SysCurPno=BufCurPno;
}
/*------------------------------------*/
void  run_pcb_msg(void);
void  run_pcb_msg(void)
{
  MSG FAR *input;
  PCB FAR *CurPCB;

  if(!is_new_msg())
  return;

  input=(MSG FAR *)get_self_msg();

  SysCurPno=input->dest.pno;
  if(SysCurPno<MAX_PCB_NUM)
  {
    CurPCB = (PCB FAR *)&PCBPool[SysCurPno];
    CurPCB->input=(BFAR *)input;
    CurPCB->lastevent=CurPCB->thisevent;
    CurPCB->thisevent=input->event;
    EXEPROC(SysCurPno,(BFAR *)input+sizeof(MSG));
  }

  free_self_msg();
}


/*===========================================================================*/


/*------------------------------------*/
VFAR NEXT(WORD state);
VFAR NEXT(WORD state)
{
  PCB *CurPCB;
  WORD stack;
  CurPCB=&PCBPool[SysCurPno];
  CurPCB->laststate=CurPCB->thisstate;
  CurPCB->thisstate=state;
  stack=PATPool[SysCurPno].stack;
  next_ret(stack);                          /*ReStore Old SP in OS*/
}

/*------------------------------------*/
WFAR STATE(void);
WFAR STATE()
{
  return(PCBPool[SysCurPno].thisstate);
}
/*------------------------------------*/
WFAR EVENT(void);
WFAR EVENT()
{
  return(PCBPool[SysCurPno].thisevent);
}
/*------------------------------------*/
WFAR LENGTH(void);
WFAR LENGTH()                    /*If TimeOutEvent,Invalid*/
{
  MSG FAR *ptr;
  ptr=(MSG FAR *)PCBPool[SysCurPno].input;
  return(ptr->leng);
}
/*------------------------------------*/
VFAR SENDER(PID FAR * sender);
VFAR SENDER(PID FAR * sender)       /*If TimeOutEvent,Invalid*/
{
	PID *sour;
	sour=(PID *)(PCBPool[SysCurPno].input+sizeof(PID));
    sender->pno=sour->pno;
	sender->unit=sour->unit;
	sender->module=sour->module;
}
/*------------------------------------*/
VFAR SELF(PID FAR * self);
VFAR SELF(PID FAR * self)
{
  self->pno=SysCurPno;
  self->unit=2;
  self->module=2;
}


/*End Of r_pcb.c*/
