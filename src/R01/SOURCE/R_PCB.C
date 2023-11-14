#ifdef  __BORLANDC__
#include <mem.h>
#else
#include <memory.h>
#endif

#include  <dos.h>
#include  <stdlib.h>
#include "zxj10.h"
#include "zxevent.h"
#include "zxhard.h"

#include "r_mem.h"
#include "r_msg.h"
#include "r_pcb.h"
#include "r_tcb.h"
#include "r_pat.h"

PCB far *PCBPool;
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
  TAG   far *lastptr;
  TAG   far *itemptr;
  TAG   far *nextptr;

  lastptr =(TAG far*)&(PCBPool[last].tag);
  root=lastptr->root;
  next=lastptr->next;
  lastptr->next=item;

  itemptr =(TAG far*)&(PCBPool[item].tag);
  itemptr->next=next;
  itemptr->last=last;
  itemptr->root=root;

  nextptr =(TAG far*)&(PCBPool[next].tag);
  nextptr->last=item;
}
/*------------------------------------*/
/*Put a TAG Befor one TAG*/
static  void  BeforeTAG(WORD next,WORD item);
static  void  BeforeTAG(WORD next,WORD item)
{
  WORD  last,root;
  TAG   far *nextptr;
  TAG   far *itemptr;
  TAG   far *lastptr;

  nextptr =(TAG far*)&(PCBPool[next].tag);
  root=nextptr->root;
  last=nextptr->last;
  nextptr->last=item;

  itemptr =(TAG far*)&(PCBPool[item].tag);
  itemptr->next=next;
  itemptr->last=last;
  itemptr->root=root;

  lastptr =(TAG far*)&(PCBPool[last].tag);
  lastptr->next=item;
}
/*------------------------------------*/
/*Delete a TAG From Queue */
static  void  DeleteTAG(WORD item);
static  void  DeleteTAG(WORD item)
{
  WORD last,next;
  TAG   far *itemptr;
  TAG   far *lastptr;
  TAG   far *nextptr;

  itemptr =(TAG far*)&(PCBPool[item].tag);
  last=itemptr->last;
  itemptr->last=item;
  next=itemptr->next;
  itemptr->next=item;
  itemptr->root=item;

  lastptr =(TAG far*)&(PCBPool[last].tag);
  lastptr->next=next;

  nextptr =(TAG far*)&(PCBPool[next].tag);
  nextptr->last=last;
}
/*------------------------------------*/
/*Make a TAG Is a Root In Queue */
static  void  QueueTAG(WORD item);
static  void  QueueTAG(WORD item)
{
  TAG   far *itemptr;

  itemptr =(TAG far*)&(PCBPool[item].tag);
  itemptr->next=item;
  itemptr->last=item;
  itemptr->root=item;
}
/*===========================================================================*/
/*------------------------------------*/
void  ini_pcb_queue(void);
void  ini_pcb_queue()
{
  WORD  ii,jj;
  WORD  tno;

  ini_self_msg();
  ini_tcb_queue();

  ii=(MAX_PCB_NUM+PCB_QUEUE_NUM)*sizeof(PCB);
  PCBPool=(PCB far *)alloc_ram(ii);

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

  next=GetNextTAG(queue);
  for(;;)
  {
    if(next==queue) break;            /*No More Timer Process To execute*/
    SysCurPno=next;

    PCBPool[SysCurPno].thisevent=0;
    EXEPROC((BYTE far *)&tick);
    next=GetNextTAG(next);
  }
}
/*------------------------------------*/
void  run_pcb_msg(void);
void  run_pcb_msg(void)
{
  MSG far *input;
  PCB far *CurPCB;

  if(SelfMsgBuf.Head==SelfMsgBuf.Tail)
  return;

  input=(MSG far *)get_self_msg();

  SysCurPno=input->dest.pno;
  if(SysCurPno<MAX_PCB_NUM)
  {
    CurPCB = (PCB far *)&PCBPool[SysCurPno];
    CurPCB->input=(BYTE far *)input;
    CurPCB->lastevent=CurPCB->thisevent;
    CurPCB->thisevent=input->event;
    EXEPROC((BYTE far *)input+sizeof(MSG));
  }

  free_self_msg();
}
/*------------------------------------*/
void  run_pcb_tcb(void);
void  run_pcb_tcb(void)
{
  TCB far *input;
  PCB far *CurPCB;
  WORD item;

  item=get_tcb_arrived();
  if(item==TimerBusyQueue)
  return;

  input=(TCB far *)&TCBPool[item];

  SysCurPno=(WORD)input->pno;
  if(SysCurPno<MAX_PCB_NUM)
  {
    CurPCB = (PCB far *)&PCBPool[SysCurPno];
    if(input->tno>=0x80)
    {                                 /*SET_TIMER,else EXTRA_SET_TIMER*/
      input->tno &= 0x07;
      CurPCB->timer[input->tno]=0xffff;
    }
    CurPCB->input=(BYTE far *)input;
    CurPCB->lastevent=CurPCB->thisevent;
    CurPCB->thisevent=Timer1Event+(WORD)input->tno;
    EXEPROC((BYTE far *)&(input->csn));
  }

  free_tcb_arrived(item);
}

/*===========================================================================*/
/*------------------------------------*/
void NEXT_STATE(WORD state);
void NEXT_STATE(WORD state)
{
  PCB *CurPCB;
  CurPCB=&PCBPool[SysCurPno];
  CurPCB->laststate=CurPCB->thisstate;
  CurPCB->thisstate=state;
  NEXTRET();                          /*ReStore Old SP in OS*/
}
/*------------------------------------*/
WORD far STATE(void);
WORD far STATE()
{
  return(PCBPool[SysCurPno].thisstate);
}
/*------------------------------------*/
WORD far EVENT(void);
WORD far EVENT()
{
  return(PCBPool[SysCurPno].thisevent);
}
/*------------------------------------*/
WORD far LENGTH(void);
WORD far LENGTH()                    /*If TimeOutEvent,Invalid*/
{
  MSG far *ptr;
  ptr=(MSG far *)PCBPool[SysCurPno].input;
  return(ptr->leng);
}
/*------------------------------------*/
void SENDER(PID far * sender);
void SENDER(PID far * sender)       /*If TimeOutEvent,Invalid*/
{
  _fmemcpy(sender,PCBPool[SysCurPno].input+sizeof(PID),sizeof(PID));
}
/*------------------------------------*/
void SELF_PID(PID far * self);
void SELF_PID(PID far * self)
{
  self->pno=SysCurPno;
  self->unit=2;
  self->module=2;
}
/*------------------------------------*/
void far CREATE(WORD pno,BYTE tno,void far *entry);
void far CREATE(WORD pno,BYTE tno,void far *entry)
{
  long tick;
  BYTE maste,slave;

  if(pno>63)  return;
  if(tno>5)   return;
  maste=_GetEXRegByte(DOS_OCW1M);
  slave=_GetEXRegByte(DOS_OCW1S);
  _SetEXRegByte(DOS_OCW1M,0xfb);
  _SetEXRegByte(DOS_OCW1S,0xff);
  DeleteTAG(pno);
  set_pat_tno(pno,tno);
  set_pat_entry(pno,entry);
  BeforeTAG(ProIdleQueue+tno,pno);
  _SetEXRegByte(DOS_OCW1S,slave);
  _SetEXRegByte(DOS_OCW1M,maste);

  if(tno != 0) return;
  tick=0;
  PCBPool[pno].thisstate=0;
  SendToSelf(0,(BYTE  far *)&tick,4,pno,SysCurPno);
}
/*Example:CREATE(2,1,(void far *)&MyProc);*/

/*End Of r_pcb.c*/
