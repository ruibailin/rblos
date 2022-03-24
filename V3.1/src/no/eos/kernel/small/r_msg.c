
/*------------------------------------
 * r_msg.c
 * Create:  2021-10-16
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
#if EOS_SMALL_MODE
/*================================================================*/
#include "node.h"

typedef struct{
	unsigned short   dest;
	unsigned short   sour;
	unsigned short   event;
	unsigned short	  length;
	void  *body;
}MSG;

#define	MSG_LIST_NUM	2
#define   EventIdleQueue    0
#define	  EventBusyQueue	1
#define	MSG_NODE_NUM	MAX_MSG_NUM+MSG_LIST_NUM
#if(MSG_NODE_NUM > 32767)
#error
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
#define  get_node_next(node)	((int)NodePool[(node)].next)&0xffff
#define  get_node_last(node)	((int)NodePool[(node)].last)&0xffff
#define  get_node_root(node)	((int)NodePool[(node)].root)&0xffff


/**********************MSG***************************************/
/*------------------------------------*/
static void ini_idle_list(int start);
static void ini_idle_list(int start)
{
	int ii;
	for(ii=start;ii<MSG_NODE_NUM;ii++)
	{
		BeforeNode(NodePool,EventIdleQueue,ii);
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
	DeleteNode(NodePool,node);
	node_msg=node;
	MSGPool[node_msg].sour=(unsigned short)s;
	MSGPool[node_msg].event=(unsigned short)eve;
	MSGPool[node_msg].length=(unsigned short)len;
	return(node);
}

/*------------------------------------*/
void set_busy_msg(int node,int d,void *out);
void set_busy_msg(int node,int d,void *out)
{
	int	root;
	int node_msg;	/*for MSG list*/
	node_msg=node;
	MSGPool[node_msg].dest=(unsigned short)d;
	MSGPool[node_msg].body=out;
	root=EventBusyQueue;
	BeforeNode(NodePool,root,node);
}

/*------------------------------------*/
int	get_msg_arrived(void);
int get_msg_arrived()
{
  int root,next;
  root=EventBusyQueue;
  next=get_node_next(root);
  if(next == root)	return(EventIdleQueue);
  DeleteNode(NodePool,next);
  return(next);
}
/*------------------------------------*/
void free_msg_arrived(int node);
void free_msg_arrived(int node)
{
  int root;
  root=EventIdleQueue;
  BeforeNode(NodePool,root,node);     /*Add node to Idle Queue*/
}
/*------------------------------------*/
int	get_msg_dest(int node);
int get_msg_dest(int node)
{
  int dest;
  dest=((int)MSGPool[node].dest)&0xffff;
  return(dest);
}
/*------------------------------------*/
int	get_msg_sour(int node);
int get_msg_sour(int node)
{
  int sour;
  sour=((int)MSGPool[node].sour)&0xffff;
  return(sour);
}
/*------------------------------------*/
int	get_msg_event(int node);
int get_msg_event(int node)
{
  int event;
  event=((int)MSGPool[node].event)&0xffff;
  return(event);
}

/*------------------------------------*/
int	get_msg_length(int node);
int get_msg_length(int node)
{
  int length;
  length=((int)MSGPool[node].length)&0xffff;
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
#include	"../r_pat.h"
void ini_pcb_msg(void);
void ini_pcb_msg(void)
{
	ini_all_node();
	ini_idle_list(MAX_PAT_NUM);
}
/*------------------------------------*/
void set_pcb_msg(int node,int d,void *out);
void set_pcb_msg(int node,int d,void *out)
{
	MSGPool[node].dest=(unsigned char)d;
	MSGPool[node].body=out;
	BeforeNode(NodePool,d,node);
}
/*------------------------------------*/
int	get_pcb_msg(int pcb);
int get_pcb_msg(int pcb)
{
  int root,next;
  root=pcb;
  next=get_node_next(root);
  if(next == root)	return(EventIdleQueue);
  DeleteNode(NodePool,next);
  return(next);
}
/*================================================================*/
#endif
/* end of r_msg.c */
