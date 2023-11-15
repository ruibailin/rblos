
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

#include "0ctr.h"
#ifdef EOS_TINY_MODE
#include "node.h"
/*================================================================*/
#define   TimerIdleQueue     0
#define   TimerL50msQueue    1
#define   Timer50msQueue     2
#define   TimerBusyQueue     3

#define		TCB_LIST_NUM	TimerBusyQueue+1
#define		TCB_NODE_NUM	MAX_TCB_NUM+TCB_LIST_NUM
#if(TCB_NODE_NUM > 254)
#error
#endif
/*------------------------------------*/
typedef struct{
  unsigned short  len;
  unsigned short  rst;
  unsigned char  tno;
  unsigned char  pno;
}TCB;

/*------------------------------------*/

static	TCB	 TCBPool[TCB_NODE_NUM];
static	Node NodePool[TCB_NODE_NUM];

/*------------------------------------*/
/*initiate all node for future use */
static	void  ini_all_node(void);
static	void  ini_all_node(void)
{
  unsigned char ii;
  for(ii=0;ii<TCB_NODE_NUM;ii++)
  {
	QueueNode(NodePool,ii);
  }
}

/*------------------------------------*/
#define  get_node_next(node)	((int)NodePool[(node)].next)&0xff
#define  get_node_last(node)	((int)NodePool[(node)].last)&0xff
#define  get_node_root(node)	((int)NodePool[(node)].root)&0xff


/*================================================================*/

/*------------------------------------*/
static  int  FindQueue(int  len);
static  int  FindQueue(int  len)
{
    return(Timer50msQueue);
}
/*------------------------------------*/
static void ini_list_head(void);
static void ini_list_head(void)
{
	TCBPool[TimerL50msQueue].len=0;
	TCBPool[Timer50msQueue].len=5;
}
/*------------------------------------*/
static void ini_idle_list(void);
static void ini_idle_list(void)
{
	int ii;
	for(ii=TCB_LIST_NUM;ii<TCB_NODE_NUM;ii++)
	{
		BeforeNode(NodePool,TimerIdleQueue,ii);
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
	node=get_node_next(TimerIdleQueue);
	DeleteNode(NodePool,node);
	TCBPool[node].tno=(unsigned char)tno;
	TCBPool[node].pno=(unsigned char)pno;
	return(node);
}

/*------------------------------------*/
void set_node_tcb(int node,int len);
void set_node_tcb(int node,int len)
{
	int		root;							/*for common list*/

	TCB		*node_ptr,*root_ptr;

	node_ptr=(TCB  *)&(TCBPool[node]);
	node_ptr->len=(unsigned short)len;

	if(len < 5)
	{
		if(len == 0)
			root=TimerBusyQueue;
		else
			root=TimerL50msQueue;
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
    case   TimerIdleQueue:
			return;
    case   TimerL50msQueue:
    case   TimerBusyQueue:
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
  BeforeNode(NodePool,TimerIdleQueue,node);
}
/*------------------------------------*/
/*One Way To dec timer(only for L50msque)*/
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
		BeforeNode(NodePool,TimerBusyQueue,node);
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
  unsigned short len;

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
    set_node_tcb(node,len);                    /*Time Out in this queue*/

    if(next == root)
    break;                                /*Meet Queue Tail */

    node=next;                            /*Timer (node) arrived*/
    if(TCBPool[node].rst != 0)
    break;                                 /*No More time-out TCB Arrived*/
  }
}
/*===========================================================================*/

/*------------------------------------*/
void run_tcb_list(void);
void run_tcb_list()
{
  dec_tcb_node(TimerL50msQueue);
  dec_tcb_list(Timer50msQueue);
}
/*------------------------------------*/
int	get_tcb_arrived(void);
int get_tcb_arrived()
{
  int root,next;
  root=TimerBusyQueue;
  next=get_node_next(root);
  if(next == root)	return(TimerIdleQueue);
  DeleteNode(NodePool,next);
  return(next);
}
/*------------------------------------*/
void free_tcb_arrived(int node);
void free_tcb_arrived(int node)
{
  int root;
  root=TimerIdleQueue;
  BeforeNode(NodePool,root,node);     /*Add node to Idle Queue*/
}

/*------------------------------------*/
int	get_tcb_tno(int node);
int get_tcb_tno(int node)
{
  int tno;
  tno=((int)TCBPool[node].tno)&0xff;
  return(tno);
}
/*------------------------------------*/
int	get_tcb_pno(int node);
int get_tcb_pno(int node)
{
  int pno;
  pno=((int)TCBPool[node].pno)&0xff;
  return(pno);
}


/*================================================================*/
#endif
/* end of r_tcb.c */
