#include  "rbltype.h"
#include  "r_mem.h"
#include  "r_msg.h"
#include  "r_tcb.h"
#include  "r_pcb.h"
#include  "r_pat.h"


TCB FAR *TCBPool;
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
  TAG   FAR *lastptr;
  TAG   FAR *itemptr;
  TAG   FAR *nextptr;
  lastptr =(TAG FAR*)&(TCBPool[last].tag);
  root=lastptr->root;
  next=lastptr->next;
  lastptr->next=item;

  itemptr =(TAG FAR*)&(TCBPool[item].tag);
  itemptr->next=next;
  itemptr->last=last;
  itemptr->root=root;

  nextptr =(TAG FAR*)&(TCBPool[next].tag);
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

  nextptr =(TAG FAR*)&(TCBPool[next].tag);
  root=nextptr->root;
  last=nextptr->last;
  nextptr->last=item;

  itemptr =(TAG FAR*)&(TCBPool[item].tag);
  itemptr->next=next;
  itemptr->last=last;
  itemptr->root=root;

  lastptr =(TAG FAR*)&(TCBPool[last].tag);
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

  itemptr =(TAG FAR*)&(TCBPool[item].tag);
  last=itemptr->last;
  itemptr->last=item;
  next=itemptr->next;
  itemptr->next=item;
  itemptr->root=item;

  lastptr =(TAG FAR*)&(TCBPool[last].tag);
  lastptr->next=next;

  nextptr =(TAG FAR*)&(TCBPool[next].tag);
  nextptr->last=last;

}
/*------------------------------------*/
/*Make a TAG Is a Root In Queue */
static  void  QueueTAG(WORD item);
static  void  QueueTAG(WORD item)
{
  TAG   FAR *itemptr;

  itemptr =(TAG FAR*)&(TCBPool[item].tag);
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
  TCB  FAR *rootptr;
  TCB  FAR *itemptr;

  DeleteTAG(item);
  itemptr=(TCB FAR *)&(TCBPool[item]);
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
  rootptr=(TCB FAR *)&(TCBPool[root]);

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
  TCB FAR *rootptr;
  TCB FAR *itemptr;

  rootptr=(TCB FAR *)&(TCBPool[root]);
  if(rootptr->rst == 0)
  return;                                 /*Queue Is Empty*/
  rootptr->rst --;

  item=rootptr->tag.next;
  itemptr=(TCB FAR *)&(TCBPool[item]);
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
VFAR ini_tcb_queue(void);
VFAR ini_tcb_queue()
{
  WORD  ii;

  ii=(MAX_TCB_NUM+TCB_QUEUE_NUM)*sizeof(TCB);
  TCBPool=(TCB  FAR *)alloc_ram(ii);

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
VFAR run_tcb_queue(void);
VFAR run_tcb_queue()
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
WFAR get_tcb_arrived(void);
WFAR get_tcb_arrived()
{
  WORD item;
  item=GetNextTAG(TimerBusyQueue);
  if(item != TimerBusyQueue)
  DeleteTAG(item);
  return(item);
}
/*------------------------------------*/
VFAR free_tcb_arrived(WORD item);
VFAR free_tcb_arrived(WORD item)
{
  AppendTAG(TimerIdleQueue,item);      /*Add item to Idle Queue*/
}

/*------------------------------------*/
VFAR  send_tcb_msg(void);
VFAR  send_tcb_msg(void)
{
  TCB FAR *input;
  WORD item;

  WORD event;
  WORD d_pno;
  item=get_tcb_arrived();
  if(item==TimerBusyQueue)
  return;
  input=(TCB FAR *)&TCBPool[item];
  event=Timer1Event+input->tno;
  d_pno=input->pno;
  SendToSelf(event,(BFAR *)input,sizeof(TCB),d_pno,0);
  free_tcb_arrived(item);
}

/*===========================================================================*/
extern  WORD  SysCurPno;

/*------------------------------------*/
VFAR SET(WORD  len,WORD  tno);
VFAR SET(WORD  len,WORD  tno)
{
  WFAR *tid;
  TCB  FAR *tcb;
  WORD item;
  if(PATPool[SysCurPno].task!=0) return;

  tid=(WFAR *)&(PCBPool[SysCurPno].timer[tno]);
  if(*tid<MAX_TCB_NUM)
  {
    reset_tcb(*tid);
  }

  item = GetNextTAG(TimerIdleQueue);
  if(item == TimerIdleQueue)
  {
   tid=0xffff;
   return;
  }
  *tid=item;
  
  tcb=(TCB FAR *)&(TCBPool[item]);
  tcb->tno=(WORD)(tno);
  tcb->pno=(WORD)SysCurPno;
  tcb->len=len;
  set_tcb(item);
}
/*------------------------------------*/
VFAR KILL(WORD  tno);
VFAR KILL(WORD  tno)
{
  WFAR *tid;
  if(PATPool[SysCurPno].task!=0) return;

  tid=(WFAR *)&(PCBPool[SysCurPno].timer[tno]);
  if(*tid>=MAX_TCB_NUM)
  return;

  reset_tcb(*tid);
  *tid=0xffff;
}
/*The End of r_tcb.c */

