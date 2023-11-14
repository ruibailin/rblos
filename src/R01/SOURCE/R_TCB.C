#include  <dos.h>
#include  <stdlib.h>

#include  "zxhard.h"
#include  "zxj10.h"
#include  "r_mem.h"
#include  "r_tcb.h"
#include  "r_pcb.h"

TCB far *TCBPool;
/*------------------------------------*/
/*Get Last TAG After A TAG*/
#define  GetLastTAG(item)  TCBPool[(item)].tag.last
/*------------------------------------*/
/*Get Next TAG After A TAG*/
#define  GetNextTAG(item)  TCBPool[(item)].tag.next
/*------------------------------------*/
/*Macro Judge whether a TAG is in a queue*/
#define  GetFirstTAG(item)  TCBPool[(item)].tag.root
/*------------------------------------*/
/*Browse a TAG In Queue */
static  void  BrowseTAG(WORD item);
void  BrowseTAG(WORD item)
{
  WORD next;
  next=TCBPool[item].tag.next;
  for(;;)
  {
    if(next == item) break;
    next=TCBPool[next].tag.next;
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

  lastptr =(TAG far*)&(TCBPool[last].tag);
  root=lastptr->root;
  next=lastptr->next;
  lastptr->next=item;

  itemptr =(TAG far*)&(TCBPool[item].tag);
  itemptr->next=next;
  itemptr->last=last;
  itemptr->root=root;

  nextptr =(TAG far*)&(TCBPool[next].tag);
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

  nextptr =(TAG far*)&(TCBPool[next].tag);
  root=nextptr->root;
  last=nextptr->last;
  nextptr->last=item;

  itemptr =(TAG far*)&(TCBPool[item].tag);
  itemptr->next=next;
  itemptr->last=last;
  itemptr->root=root;

  lastptr =(TAG far*)&(TCBPool[last].tag);
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

  itemptr =(TAG far*)&(TCBPool[item].tag);
  last=itemptr->last;
  itemptr->last=item;
  next=itemptr->next;
  itemptr->next=item;
  itemptr->root=item;

  lastptr =(TAG far*)&(TCBPool[last].tag);
  lastptr->next=next;

  nextptr =(TAG far*)&(TCBPool[next].tag);
  nextptr->last=last;
}
/*------------------------------------*/
/*Make a TAG Is a Root In Queue */
static  void  QueueTAG(WORD item);
static  void  QueueTAG(WORD item)
{
  TAG   far *itemptr;

  itemptr =(TAG far*)&(TCBPool[item].tag);
  itemptr->next=item;
  itemptr->last=item;
  itemptr->root=item;
}
/*------------------------------------*/
static  WORD  FindQueue(WORD  len);
static  WORD  FindQueue(WORD  len)
{
  if(len>=100)
  {
    if(len<500)
    return(Timer1sQueue);
    if(len<1000)
    return(Timer5sQueue);
    if(len<5000)
    return(Timer10sQueue);

    return(Timer50sQueue);
  }
  else
  {
    if(len>=50)
    return(Timer500msQueue);
    if(len>=10)
    return(Timer100msQueue);

    return(Timer50msQueue);
  }
}
/*===========================================================================*/
/*------------------------------------*/
static  void set_tcb(WORD item);
static  void set_tcb(WORD item)
{
  WORD  root,rootlen;
  TCB  far *rootptr;
  TCB  far *itemptr;

  DeleteTAG(item);
  itemptr=(TCB far *)&(TCBPool[item]);
  if(itemptr->len < 5)
  {
    if(itemptr->len == 0)
    root=TimerBusyQueue;
    else
    root=TimerL50msQueue;

    BeforeTAG(root,item);
    return;
  }
  root=FindQueue(itemptr->len);
  BeforeTAG(root,item);        /*Put the TCB in tail of Queue*/
  rootptr=(TCB far *)&(TCBPool[root]);

  rootlen=rootptr->len;
  itemptr->len = itemptr->len - rootlen;
  itemptr->rst = rootlen - rootptr->rst;
  rootptr->rst = rootlen;
}
/*------------------------------------*/
static  void reset_tcb(WORD item);
static  void reset_tcb(WORD item)
{
  WORD next,root;
  root=GetFirstTAG(item);
  if(root == item)
  return;     /*Avoid To Kill Timer When Timer Is Out*/
  switch(root)
  {
    case   TimerIdleQueue:
           break;
    case   TimerL50msQueue:
    case   TimerBusyQueue:
           DeleteTAG(item);
           AppendTAG(TimerIdleQueue,item);
           break;
    default:
           next=GetNextTAG(item);
           if(next == root)            /*Next Is Root?*/
           TCBPool[root].rst -= TCBPool[item].rst;
           else
           TCBPool[next].rst += TCBPool[item].rst;

           DeleteTAG(item);
           AppendTAG(TimerIdleQueue,item);
           break;
  }
}
/*-----One Way To Set Timer-------------*/
static  void dec_tcb_member(WORD  root);
static  void dec_tcb_member(WORD  root)
{
  WORD item,next;
  item=GetNextTAG(root);
  if(item == root)
  return;                                 /*Queue Is Empty*/

  for(;;)
  {
    next=GetNextTAG(item);
    if(TCBPool[item].len != 0)
    TCBPool[item].len--;
    else
    {
      DeleteTAG(item);
      BeforeTAG(TimerBusyQueue,item);
    }
    if(next == root)
    break;                                /*Meet Queue Tail */
    item=next;
  }
}
/*-----Other Way To Set Timer-------------*/
static  void dec_tcb_queue(WORD  root);
static  void dec_tcb_queue(WORD  root)
{
  WORD item,next;
  TCB far *rootptr;
  TCB far *itemptr;

  rootptr=(TCB far *)&(TCBPool[root]);
  if(rootptr->rst == 0)
  return;                                 /*Queue Is Empty*/
  rootptr->rst --;

  item=rootptr->tag.next;
  itemptr=(TCB far *)&(TCBPool[item]);
  itemptr->rst --;
  if(itemptr->rst != 0)
  return;                                 /*No TCB Arrived*/

  for(;;)
  {
    next=GetNextTAG(item);
    set_tcb(item);                        /*Time Out*/

    if(next == root)
    break;                                /*Meet Queue Tail */

    item=next;                            /*Timer (item) arrived*/
    if(TCBPool[item].rst != 0)
    break;                                 /*No More TCB Arrived*/
  }
}
/*===========================================================================*/
/*------------------------------------*/
void far ini_tcb_queue(void);
void far ini_tcb_queue()
{
  WORD  ii;

  ii=(MAX_TCB_NUM+TCB_QUEUE_NUM)*sizeof(TCB);
  TCBPool=(TCB  far *)alloc_ram(ii);

  for(ii=0;ii<TCB_QUEUE_NUM;ii++)
  QueueTAG(MAX_TCB_NUM+ii);
  for(ii=0;ii<MAX_TCB_NUM;ii++)
  BeforeTAG(TimerIdleQueue,ii);

  TCBPool[Timer50msQueue].len=5;
  TCBPool[Timer100msQueue].len=10;
  TCBPool[Timer500msQueue].len=50;
  TCBPool[Timer1sQueue].len=100;
  TCBPool[Timer5sQueue].len=500;
  TCBPool[Timer10sQueue].len=1000;
  TCBPool[Timer50sQueue].len=5000;
  TCBPool[Timer100sQueue].len=10000;
}
/*------------------------------------*/
void  far run_tcb_queue(void);
void  far run_tcb_queue()
{
  dec_tcb_member(TimerL50msQueue);
  dec_tcb_queue(Timer50msQueue);
  dec_tcb_queue(Timer100msQueue);
  dec_tcb_queue(Timer500msQueue);
  dec_tcb_queue(Timer1sQueue);
  dec_tcb_queue(Timer5sQueue);
  dec_tcb_queue(Timer10sQueue);
  dec_tcb_queue(Timer50sQueue);
  dec_tcb_queue(Timer100sQueue);
}
/*------------------------------------*/
WORD  far get_tcb_arrived(void);
WORD  far get_tcb_arrived()
{
  WORD item;
  _disable();
  item=GetNextTAG(TimerBusyQueue);
  if(item != TimerBusyQueue)
  DeleteTAG(item);
  _enable();
  return(item);
}
/*------------------------------------*/
void  far free_tcb_arrived(WORD item);
void  far free_tcb_arrived(WORD item)
{
  _disable();
  AppendTAG(TimerIdleQueue,item);      /*Add item to Idle Queue*/
  _enable();
}
/*===========================================================================*/
extern  WORD  SysCurPno;
/*------------------------------------*/
WORD EXTRA_SET_TIMER(WORD len, BYTE tno, CSN ex);
WORD EXTRA_SET_TIMER(WORD len, BYTE tno, CSN ex)
{
  WORD item;
  TCB far *tcb;
  if(tno>=8)
  return(0xffff);

  _disable();
  item = GetNextTAG(TimerIdleQueue);
  if(item == TimerIdleQueue)
  {
    _enable();
    return(0xffff);
  }
  tcb=(TCB far *)&TCBPool[item];
  tcb->csn=ex;
  tcb->tno=tno;
  tcb->pno=(BYTE)SysCurPno;
  tcb->len=len;
  set_tcb(item);
  _enable();

  return(item);
}
/*------------------------------------*/
void EXTRA_KILL_TIMER(WORD tid);
void EXTRA_KILL_TIMER(WORD tid)
{
  if(tid>=MAX_TCB_NUM)
  return;

  if( SysCurPno != (WORD)(TCBPool[tid].pno))
  return;
  _disable();
  reset_tcb(tid);
  _enable();
}
/*------------------------------------*/
void far SET_TIMER(WORD  len,BYTE  tno);
void far SET_TIMER(WORD  len,BYTE  tno)
{
  WORD far *tid;
  TCB  far *tcb;
  WORD item;
  BYTE maste,slave;
  tid=(WORD far *)&(PCBPool[SysCurPno].timer[tno]);
  if(*tid<MAX_TCB_NUM)
  {
    _disable();
    reset_tcb(*tid);
    _enable();
  }

  maste=_GetEXRegByte(DOS_OCW1M);
  slave=_GetEXRegByte(DOS_OCW1S);
  _SetEXRegByte(DOS_OCW1M,0xfb);
  _SetEXRegByte(DOS_OCW1S,0xff);

  item = GetNextTAG(TimerIdleQueue);
  if(item == TimerIdleQueue)
  {
   _SetEXRegByte(DOS_OCW1S,slave);
   _SetEXRegByte(DOS_OCW1M,maste);
   *tid=0xffff;
   return;
  }
  *tid=item;
  tcb=(TCB far *)&(TCBPool[item]);
  tcb->tno=(BYTE)(tno+0x80);
  tcb->pno=(BYTE)SysCurPno;
  tcb->len=len;
  set_tcb(item);
  _SetEXRegByte(DOS_OCW1S,slave);
  _SetEXRegByte(DOS_OCW1M,maste);
}
/*------------------------------------*/
void far KILL_TIMER(BYTE  tno);
void far KILL_TIMER(BYTE  tno)
{
  WORD far *tid;
  BYTE maste,slave;
  tid=(WORD far *)&(PCBPool[SysCurPno].timer[tno]);
  if(*tid>=MAX_TCB_NUM)
  return;

  maste=_GetEXRegByte(DOS_OCW1M);
  slave=_GetEXRegByte(DOS_OCW1S);
  _SetEXRegByte(DOS_OCW1M,0xfb);
  _SetEXRegByte(DOS_OCW1S,0xff);
  reset_tcb(*tid);
  _SetEXRegByte(DOS_OCW1S,slave);
  _SetEXRegByte(DOS_OCW1M,maste);
  *tid=0xffff;
}
/*The End of r_tcb.c */

