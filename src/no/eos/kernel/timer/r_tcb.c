
/*------------------------------------
 * r_tcb.c
 * Create:  2021-10-17
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */

#include "1imp.h"

/*================================================================*/
#include "../public/node.h"
#include "r_tcb.h"
/*================================================================*/
#define   TimerL10msQHead    TimerBusyQHead+1
#define   Timer10msQHead     TimerBusyQHead+2
#define   Timer100msQHead    TimerBusyQHead+3
#define   Timer1sQHead     	 TimerBusyQHead+4

#define		TCB_LIST_NUM	 TimerBusyQHead+5
#define		TCB_NODE_NUM	 MAX_TCB_NUM+TCB_LIST_NUM
#if(TCB_NODE_NUM > MAX_UINTXX)
#error  "not enough tcb number"
#endif
/*------------------------------------*/
typedef struct{
  unsigned int  len;
  unsigned int  rst;
  uintxx  tno;
  uintxx  pno;
}TCB;

/*------------------------------------*/

static	TCB	 TCBPool[TCB_NODE_NUM];
static	Node NodePool[TCB_NODE_NUM];

/*------------------------------------*/
/*initiate all node for future use */
static	void  ini_all_node(void);
static	void  ini_all_node(void)
{
  uintxx ii;
  for(ii=0;ii<TCB_NODE_NUM;ii++)
  {
	QueueNode(NodePool,ii);
  }
}

/*------------------------------------*/
#define  get_node_next(node)	((int)NodePool[(node)].next)&MAX_UINTXX
#define  get_node_last(node)	((int)NodePool[(node)].last)&MAX_UINTXX
#define  get_node_root(node)	((int)NodePool[(node)].root)&MAX_UINTXX


/*================================================================*/

/*------------------------------------*/
static  int  FindQueue(int  len);
static  int  FindQueue(int  len)
{
	if(len<100)
		return(Timer10msQHead);
	if(len<1000)
		return(Timer100msQHead);
	return(Timer1sQHead);
}
/*------------------------------------*/
static void ini_list_head(void);
static void ini_list_head(void)
{
	TCBPool[TimerL10msQHead].len=0;
	TCBPool[Timer10msQHead].len=10;
	TCBPool[Timer100msQHead].len=100;
	TCBPool[Timer1sQHead].len=1000;
}
/*------------------------------------*/
static void ini_idle_list(void);
static void ini_idle_list(void)
{
	int ii;
	for(ii=TCB_LIST_NUM;ii<TCB_NODE_NUM;ii++)
	{
		BeforeNode(NodePool,TimerIdleQHead,ii);
	}
}
/*===========================================================================*/
/*------------------------------------*/
void ini_tcb_list(void);
void ini_tcb_list()
{
	ini_all_node();
	ini_list_head();
	ini_idle_list();
}
/*------------------------------------*/
int get_node_tcb(int tno,int pno);
int get_node_tcb(int tno,int pno)
{
	int node;
	node=get_node_next(TimerIdleQHead);
	DeleteNode(NodePool,node);
	TCBPool[node].tno=(uintxx)tno;
	TCBPool[node].pno=(uintxx)pno;
	return(node);
}

/*------------------------------------*/
void set_node_tcb(int node,int len);
void set_node_tcb(int node,int len)
{
	int		root;							/*for common list*/

	TCB		*node_ptr,*root_ptr;

	node_ptr=(TCB  *)&(TCBPool[node]);
	node_ptr->len=(unsigned int)len;

	if(len < 10)
	{
		if(len == 0)
			root=TimerBusyQHead;
		else
			root=TimerL10msQHead;
		BeforeNode(NodePool,root,node);
		return;
	}

	root=FindQueue(len);
 	root_ptr=(TCB  *)&(TCBPool[root]);
	node_ptr->len = node_ptr->len - root_ptr->len;
	node_ptr->rst = root_ptr->len - root_ptr->rst;
	root_ptr->rst = root_ptr->len;
	BeforeNode(NodePool,root,node);	/*Put the TCB in tail of Queue*/
}
/*------------------------------------*/
void reset_node_tcb(int node);
void reset_node_tcb(int node)
{
  int next,root;		/*for list*/

  root=get_node_root(node);
  if(root == node)
  return;				/*Avoid To Kill Timer When Timer Is Out*/

  switch(root)
  {
    case   TimerIdleQHead:
			return;
    case   TimerL10msQHead:
    case   TimerBusyQHead:
           break;
    default:
           next=get_node_next(node);

           if(next == root)            /*Next Is Root?*/
			TCBPool[root].rst -= TCBPool[node].rst;
           else
			TCBPool[next].rst += TCBPool[node].rst;
           break;
  }
  DeleteNode(NodePool,node);
  BeforeNode(NodePool,TimerIdleQHead,node);
}
/*------------------------------------*/
/*One Way To dec timer(only for L10ms queue due to efficiency)*/
static  void dec_tcb_node(int  root);
static  void dec_tcb_node(int  root)
{
  int node,next;			/*for common list*/

  node=get_node_next(root);
  if(node == root)
  return;                                 /*Queue Is Empty*/

  for(;;)
  {
    next=get_node_next(node);
    if(TCBPool[node].len != 0)
		TCBPool[node].len--;
    else
    {
		DeleteNode(NodePool,node);
		BeforeNode(NodePool,TimerBusyQHead,node);
    }
    if(next == root)    break;          /*Meet Queue Tail */
    node=next;
  }
}
/*-----Other Way To dec Timer-------------*/
static  void dec_tcb_list(int  root);
static  void dec_tcb_list(int  root)
{
  int node,next;
  unsigned int len;

  if(TCBPool[root].rst == 0)
  return;                                 /*Queue Is Empty*/
  TCBPool[root].rst --;

  node=get_node_next(root);
  TCBPool[node].rst --;
  if(TCBPool[node].rst != 0)
  return;                                 /*No TCB Arrived*/

  for(;;)
  {
    next=get_node_next(node);

	DeleteNode(NodePool,node);
	len=TCBPool[node].len;
    set_node_tcb(node,len);               /*Time Out in this queue*/

    if(next == root)
    break;                                /*Meet Queue Tail */

    node=next;                            /*Timer (node) arrived*/
    if(TCBPool[node].rst != 0)
    break;                                 /*No More time-out TCB Arrived*/
  }
}
/*===========================================================================*/

/*------------------------------------*/
void run_tcb_l10ms(void);
void run_tcb_l10ms()
{
	dec_tcb_node(TimerL10msQHead);
}
/*------------------------------------*/
void run_tcb_10ms(void);
void run_tcb_10ms()
{
	dec_tcb_list(Timer10msQHead);
}
/*------------------------------------*/
void run_tcb_100ms(void);
void run_tcb_100ms()
{
	dec_tcb_list(Timer100msQHead);
}
/*------------------------------------*/
void run_tcb_1s(void);
void run_tcb_1s()
{
	dec_tcb_list(Timer1sQHead);
}
/*------------------------------------*/
int	get_tcb_arrived(void);
int get_tcb_arrived()
{
  int root,next;
  root=TimerBusyQHead;
  next=get_node_next(root);
  if(next == root)	return(TimerIdleQHead);
  DeleteNode(NodePool,next);
  return(next);
}
/*------------------------------------*/
void free_tcb_arrived(int node);
void free_tcb_arrived(int node)
{
  int root;
  root=TimerIdleQHead;
  BeforeNode(NodePool,root,node);     /*Add node to Idle Queue*/
}

/*------------------------------------*/
int	get_tcb_tno(int node);
int get_tcb_tno(int node)
{
  int tno;
  tno=((int)TCBPool[node].tno)&MAX_UINTXX;
  return(tno);
}
/*------------------------------------*/
int	get_tcb_pno(int node);
int get_tcb_pno(int node)
{
  int pno;
  pno=((int)TCBPool[node].pno)&MAX_UINTXX;
  return(pno);
}


/*================================================================*/

/* end of sw_timer.c */
