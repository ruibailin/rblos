
/*------------------------------------
 * r_msg.c
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
#include "r_msg.h"

/*================================================================*/
typedef struct{
	uintxx   dest;
	uintxx   sour;
	uintxx   event;
	uintxx	  length;
	void  *body;
}MSG;

#define	  MSG_NODE_NUM		MAX_MSG_NUM+2
#if MAX_NODE_NUM>MAX_UNITXX
#error  "Please use another mode"
#endif

static	MSG	 MSGPool[MSG_NODE_NUM];
static	Node NodePool[MSG_NODE_NUM];

/*------------------------------------*/
/*initiate all node for future use */
static	void  ini_all_node(void);
static	void  ini_all_node(void)
{
  int ii;
  for(ii=0;ii<MSG_NODE_NUM;ii++)
  {
	QueueNode(NodePool,ii);
  }
}

/*------------------------------------*/
#define  get_node_next(node)	((int)NodePool[(node)].next)&MAX_UINTXX
#define  get_node_last(node)	((int)NodePool[(node)].last)&MAX_UINTXX
#define  get_node_root(node)	((int)NodePool[(node)].root)&MAX_UINTXX


/**********************MSG***************************************/
/*------------------------------------*/
static void ini_idle_list(void);
static void ini_idle_list()
{
	int ii;
	for(ii=2;ii<MSG_NODE_NUM;ii++)
	{
		BeforeNode(NodePool,EventIdleQHead,ii);
	}
	MSGPool[0].body=0x0L;
	MSGPool[0].dest=0;
	MSGPool[0].sour=0;
	MSGPool[0].event=0;
	MSGPool[0].length=0;

	MSGPool[1].body=0x0L;
	MSGPool[1].dest=0;
	MSGPool[1].sour=0;
	MSGPool[1].event=0;
	MSGPool[1].length=0;
}

/*===========================================================================*/
/*------------------------------------*/
void ini_msg_list(void);
void ini_msg_list()
{
	ini_all_node();
	ini_idle_list();
}

/*------------------------------------*/

int get_msg_idle(int s,int eve,int len);
int get_msg_idle(int s,int eve,int len)
{
	int node;		/*for common list*/
	int node_msg;	/*for MSG list*/
	node=get_node_next(EventIdleQHead);
	if(node == EventIdleQHead)
	{
		knl_print("message resource design is too low \n ");
		knl_panic();
		return(node);
	}
	DeleteNode(NodePool,node);
	node_msg=node;
	MSGPool[node_msg].sour=(uintxx)s;
	MSGPool[node_msg].event=(uintxx)eve;
	MSGPool[node_msg].length=(uintxx)len;
	return(node);
}

/*------------------------------------*/
void set_msg_busy(int node,int d,void *out);
void set_msg_busy(int node,int d,void *out)
{
	int	root;
	int node_msg;	/*for MSG list*/
	node_msg=node;
	MSGPool[node_msg].dest=(uintxx)d;
	MSGPool[node_msg].body=out;
	root=EventBusyQHead;
	BeforeNode(NodePool,root,node);
}

/*------------------------------------*/
int	get_msg_arrived(void);
int get_msg_arrived()
{
  int root,next;
  root=EventBusyQHead;
  next=get_node_next(root);
  if(next == root)	return(EventIdleQHead);
  DeleteNode(NodePool,next);
  return(next);
}
/*------------------------------------*/
void free_msg_arrived(int node);
void free_msg_arrived(int node)
{
  int root;
  root=EventIdleQHead;
  BeforeNode(NodePool,root,node);     /*Add node to Idle Queue*/
}
/*------------------------------------*/
int	get_msg_dest(int node);
int get_msg_dest(int node)
{
  int dest;
  dest=((int)MSGPool[node].dest)&MAX_UINTXX;
  return(dest);
}
/*------------------------------------*/
int	get_msg_sour(int node);
int get_msg_sour(int node)
{
  int sour;
  sour=((int)MSGPool[node].sour)&MAX_UINTXX;
  return(sour);
}
/*------------------------------------*/
int	get_msg_event(int node);
int get_msg_event(int node)
{
  int event;
  event=((int)MSGPool[node].event)&MAX_UINTXX;
  return(event);
}

/*------------------------------------*/
int	get_msg_length(int node);
int get_msg_length(int node)
{
  int length;
  length=((int)MSGPool[node].length)&MAX_UINTXX;
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

/*================================================================*/

/* end of msg_queue.c */
