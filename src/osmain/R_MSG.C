
#define		MAX_MSG_NUM		256
#define		MSG_LIST_NUM	2
#define		MAX_NODE_NUM	MAX_MSG_NUM+MSG_LIST_NUM
/*------------------------------------*/
/*define Node used in list*/
typedef struct{
	int		last;
	int		next;
	int		root;
} Node;
typedef struct{
	int   dest;
	int   sour;
	int   event;
	int	  length;
	void  *body;
}MSG;

/*------------------------------------*/
#define   EventIdleQueue    0
#define	  EventBusyQueue	1
static	MSG	 MSGPool[MAX_NODE_NUM];
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


/**********************MSG***************************************/
/*------------------------------------*/
static void ini_idle_list(int start);
static void ini_idle_list(int start)
{
	int ii;
	for(ii=start;ii<MAX_NODE_NUM;ii++)
	{
		BeforeNode(EventIdleQueue,ii);
	}
}

/*===========================================================================*/
/*------------------------------------*/
void ini_msg_list(void);
void ini_msg_list()
{
	ini_all_node();
	ini_idle_list(MSG_LIST_NUM);
}
/*------------------------------------*/
int get_idle_msg(int s,int eve,int len);
int get_idle_msg(int s,int eve,int len)
{
	int node;		/*for common list*/
	int node_msg;	/*for MSG list*/
	node=get_node_next(EventIdleQueue);
	DeleteNode(node);
	node_msg=node;
	MSGPool[node_msg].sour=s;
	MSGPool[node_msg].event=eve;
	MSGPool[node_msg].length=len;
	return(node);
}

/*------------------------------------*/
void set_busy_msg(int node,int d,void *out);
void set_busy_msg(int node,int d,void *out)
{
	int	root;
	int node_msg;	/*for MSG list*/
	node_msg=node;
	MSGPool[node_msg].dest=d;
	MSGPool[node_msg].body=out;
	root=EventBusyQueue;
	BeforeNode(root,node);
}

/*------------------------------------*/
int	get_msg_arrived(void);
int get_msg_arrived()
{
  int root,next;
  root=EventBusyQueue;
  next=get_node_next(root);
  if(next == root)	return(EventIdleQueue);
  DeleteNode(next);
  return(next);
}
/*------------------------------------*/
void free_msg_arrived(int node);
void free_msg_arrived(int node)
{
  int root;
  root=EventIdleQueue;
  BeforeNode(root,node);     /*Add node to Idle Queue*/
}
/*------------------------------------*/
int	get_msg_dest(int node);
int get_msg_dest(int node)
{
  int dest;
  dest=MSGPool[node].dest;
  return(dest);
}
/*------------------------------------*/
int	get_msg_sour(int node);
int get_msg_sour(int node)
{
  int sour;
  sour=MSGPool[node].sour;
  return(sour);
}
/*------------------------------------*/
int	get_msg_event(int node);
int get_msg_event(int node)
{
  int event;
  event=MSGPool[node].event;
  return(event);
}

/*------------------------------------*/
int	get_msg_length(int node);
int get_msg_length(int node)
{
  int length;
  length=MSGPool[node].length;
  return(length);
}
/*------------------------------------*/
void	*get_msg_body(int node);
void	*get_msg_body(int node)
{
  void *body;
  body=MSGPool[node].body;
  return(body);
}
/*--------used in N threaad-----------*/
#include	"r_pat.h"
void ini_pcb_msg(void);
void ini_pcb_msg(void)
{
	ini_all_node();
	ini_idle_list(PAT_LIST_NUM+MAX_PAT_NUM);
}
/*------------------------------------*/
void set_pcb_msg(int node,int d,void *out);
void set_pcb_msg(int node,int d,void *out)
{
	MSGPool[node].dest=d;
	MSGPool[node].body=out;
	BeforeNode(d,node);
}
/*------------------------------------*/
int	get_pcb_msg(int pcb);
int get_pcb_msg(int pcb)
{
  int root,next;
  root=pcb;
  next=get_node_next(root);
  if(next == root)	return(EventIdleQueue);
  DeleteNode(next);
  return(next);
}
/*The End of r_msg.c */
