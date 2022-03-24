#include	"r_tcb.h"
#define		MAX_TCB_NUM		256
#define		TCB_LIST_NUM	12
#define		MAX_NODE_NUM	MAX_TCB_NUM+TCB_LIST_NUM
/*------------------------------------*/
/*define Node used in list*/
typedef struct{
	int		last;
	int		next;
	int		root;
} Node;
typedef struct{
  int  len;
  int  rst;
  int  tno;
  int  pno;
}TCB;

/*------------------------------------*/
#define   TimerIdleQueue     0
#define   TimerL50msQueue    1
#define   Timer50msQueue     2
#define   Timer100msQueue    3
#define   Timer500msQueue    4
#define   Timer1sQueue       5
#define   Timer5sQueue       6
#define   Timer10sQueue      7
#define   Timer50sQueue      8
#define   Timer100sQueue     9
#define   TimerBusyQueue     10
static	TCB	 TCBPool[MAX_NODE_NUM];
static	Node NodePool[MAX_NODE_NUM];

/*------------------------------------*/
/*Make a Node Is a Root In Queue */
static	void  QueueNode(int item);
static	void  QueueNode(int item)
{
  Node   *itemptr;

  itemptr =&(NodePool[item]);
  itemptr->next=item;
  itemptr->last=item;
  itemptr->root=item;

}

/*------------------------------------*/
/*Put a Node after one Node*/
static	void  AppendNode(int last,int item);
static	void  AppendNode(int last,int item)
{
  int  next,root;
  Node   *lastptr;
  Node   *itemptr;
  Node   *nextptr;
  lastptr =&(NodePool[last]);
  root=lastptr->root;
  next=lastptr->next;
  lastptr->next=item;

  itemptr =&(NodePool[item]);
  itemptr->next=next;
  itemptr->last=last;
  itemptr->root=root;

  nextptr =&(NodePool[next]);
  nextptr->last=item;
}
/*------------------------------------*/
/*Put a Node Befor one Node*/
static	void  BeforeNode(int next,int item);
static	void  BeforeNode(int next,int item)
{
  int  last,root;
  Node   *nextptr;
  Node   *itemptr;
  Node   *lastptr;

  nextptr =&(NodePool[next]);
  root=nextptr->root;
  last=nextptr->last;
  nextptr->last=item;

  itemptr =&(NodePool[item]);
  itemptr->next=next;
  itemptr->last=last;
  itemptr->root=root;

  lastptr =&(NodePool[last]);
  lastptr->next=item;

}
/*------------------------------------*/
/*Delete a Node From Queue */
static	void  DeleteNode(int item);
static	void  DeleteNode(int item)
{
  int last,next;
  Node   *itemptr;
  Node   *lastptr;
  Node   *nextptr;

  itemptr =&(NodePool[item]);
  next=itemptr->next;
  if(next == item)	 return;
  last=itemptr->last;
  itemptr->last=item;
  next=itemptr->next;
  itemptr->next=item;
  itemptr->root=item;

  lastptr =&(NodePool[last]);
  lastptr->next=next;

  nextptr =&(NodePool[next]);
  nextptr->last=last;

}
/*------------------------------------*/
/*Find a Node In A Queue */
static	int  LocateNode(int root,int item);
static	int  LocateNode(int root,int item)
{
  int next;
  next=NodePool[root].next;
  for(;;)
  {
    if(next == root)	return(root);	/*no find*/
	if(next == item)	return(item);	/*find the node*/
    next=NodePool[next].next;
  }
}


/*------------------------------------*/
/*Browse a Node In Queue */
static	int  BrowseNode(int root);
static	int  BrowseNode(int root)
{
  int next,size;
  size=0;
  next=NodePool[root].next;
  for(;;)
  {
    if(next == root) break;
    next=NodePool[next].next;
	size++;
  }
  return(size);
}

/*------------------------------------*/
/*initiate all node for future use */
static	void  ini_all_node(void);
static	void  ini_all_node(void)
{
  int ii;
  for(ii=0;ii<MAX_NODE_NUM;ii++)
  {
	QueueNode(ii);
  }
}

/*------------------------------------*/
#define  get_node_next(node)	NodePool[(node)].next
#define  get_node_last(node)	NodePool[(node)].last
#define  get_node_root(node)	NodePool[(node)].root


/**********************Time Control Buffer***************************************/

/*------------------------------------*/
static  int  FindQueue(int  len);
static  int  FindQueue(int  len)
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
/*------------------------------------*/
static void ini_list_head(void);
static void ini_list_head(void)
{
	TCBPool[TimerL50msQueue].len=0;
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
static void ini_idle_list(void);
static void ini_idle_list(void)
{
	int ii;
	for(ii=TCB_LIST_NUM;ii<MAX_NODE_NUM;ii++)
	{
		BeforeNode(TimerIdleQueue,ii);
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
	DeleteNode(node);
	TCBPool[node].tno=tno;
	TCBPool[node].pno=pno;
	return(node);
}

/*------------------------------------*/
void set_node_tcb(int node,int len);
void set_node_tcb(int node,int len)
{
	int		root;							/*for common list*/

	TCB		*node_ptr,*root_ptr;

	node_ptr=(TCB  *)&(TCBPool[node]);
	node_ptr->len=len;
	
	if(len < 5)
	{
		if(len == 0)
			root=TimerBusyQueue;
		else
			root=TimerL50msQueue;
		BeforeNode(root,node);
		return; 
	}

	root=FindQueue(len);
 	root_ptr=(TCB  *)&(TCBPool[root]);
	node_ptr->len = node_ptr->len - root_ptr->len;
	node_ptr->rst = root_ptr->len - root_ptr->rst;
	root_ptr->rst = root_ptr->len;
	BeforeNode(root,node);	/*Put the TCB in tail of Queue*/
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
  DeleteNode(node);
  BeforeNode(TimerIdleQueue,node);
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
		DeleteNode(node);
		BeforeNode(TimerBusyQueue,node);
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
  int len;

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

	DeleteNode(node);
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
  dec_tcb_list(Timer100msQueue);
  dec_tcb_list(Timer500msQueue);
  dec_tcb_list(Timer1sQueue);
  dec_tcb_list(Timer5sQueue);
  dec_tcb_list(Timer10sQueue);
  dec_tcb_list(Timer50sQueue);
  dec_tcb_list(Timer100sQueue);
}
/*------------------------------------*/
int	get_tcb_arrived(void);
int get_tcb_arrived()
{
  int root,next;
  root=TimerBusyQueue;
  next=get_node_next(root);
  if(next == root)	return(TimerIdleQueue);
  DeleteNode(next);
  return(next);
}
/*------------------------------------*/
void free_tcb_arrived(int node);
void free_tcb_arrived(int node)
{
  int root;
  root=TimerIdleQueue;
  BeforeNode(root,node);     /*Add node to Idle Queue*/
}

/*------------------------------------*/
int	get_tcb_tno(int node);
int get_tcb_tno(int node)
{
  int tno;
  tno=TCBPool[node].tno;
  return(tno);
}
/*------------------------------------*/
int	get_tcb_pno(int node);
int get_tcb_pno(int node)
{
  int pno;
  pno=TCBPool[node].pno;
  return(pno);
}

/*The End of r_tcb.c */

