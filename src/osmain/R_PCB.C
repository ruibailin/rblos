#include	"r_pat.h"
#include	"r_msg.h"
#define		MAX_PCB_NUM		MAX_PAT_NUM
#define		PCB_LIST_NUM	PAT_LIST_NUM
#define		MAX_NODE_NUM	MAX_PCB_NUM+PCB_LIST_NUM
/*------------------------------------*/
/*define Node used in list*/
typedef struct{
	int		last;
	int		next;
	int		root;
} Node;
typedef struct{
	int   state;
	int   event;
	int	  stack;
	int   timer[8];
}PCB;

/*------------------------------------*/

static	PCB	 PCBPool[MAX_NODE_NUM];
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
	PCBPool[ii].state=0;
	PCBPool[ii].event=0;
  }
}

/*------------------------------------*/
#define  get_node_next(node)	NodePool[(node)].next
#define  get_node_last(node)	NodePool[(node)].last
#define  get_node_root(node)	NodePool[(node)].root


/*===========================================================================*/
/*------------------------------------*/
int	get_pcb_state(int pcb);
int	get_pcb_state(int pcb)
{
	int state;
	state=PCBPool[pcb].state;
	return(state);
}
/*------------------------------------*/
void	set_pcb_state(int pcb,int ss);
void	set_pcb_state(int pcb,int ss)
{
	PCBPool[pcb].state=ss;
}
/*------------------------------------*/
int	get_pcb_event(int pcb);
int	get_pcb_event(int pcb)
{
	int event;
	event=PCBPool[pcb].event;
	return(event);
}
/*------------------------------------*/
void	set_pcb_event(int pcb,int ee);
void	set_pcb_event(int pcb,int ee)
{
	PCBPool[pcb].event=ee;
}
/*------------------------------------*/
int	get_pcb_timer(int pcb,int tno);
int	get_pcb_timer(int pcb,int tno)
{
	int timer;
	timer=PCBPool[pcb].timer[tno];
	return(timer);
}
/*------------------------------------*/
void	set_pcb_timer(int pcb,int tno,int tt);
void	set_pcb_timer(int pcb,int tno,int tt)
{
	PCBPool[pcb].timer[tno]=tt;
}
/*------------------------------------*/
void ini_pcb_list(void);
void ini_pcb_list()
{
	int ii;
	int tno;
	ini_all_node();
	
	for(ii=PCB_LIST_NUM;ii<MAX_NODE_NUM;ii++)
	{
		tno=get_pat_tno(ii);
		BeforeNode(tno,ii);
	}
}

/*------------------------------------*/
void run_pcb_node(int pcb);
void run_pcb_node(int pcb)
{
	int ee;
	void *in;
	void ( *process)(void *in);
	ee=PCBPool[pcb].event;
	in=get_msg_body(ee);
	process=get_pat_entry(pcb);
	process(in);
}

/*------------------------------------*/
int get_pcb_next(int root);
int get_pcb_next(int root)
{
	int	next;
	next=get_node_next(root);
	return(next);
}

/*------------------------------------*/
void set_pcb_task(int pcb,int task);
void set_pcb_task(int pcb,int task)
{
	int old;
	if(pcb < PCB_LIST_NUM) return;
	if(task > (PCB_LIST_NUM-1)) return;
	old=get_pat_tno(pcb);
	if(old == task) return;
	DeleteNode(pcb);
	BeforeNode(task,pcb);
}
/*The End of r_tcb.c */
