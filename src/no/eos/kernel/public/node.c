
/*------------------------------------
 * node.c
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


#include "node.h"
/*================================================================*/
int  GetNextNode(Node *NodePool,int item);
int  GetNextNode(Node *NodePool,int item)
{
	  int next;
	  next=((int)NodePool[item].next)&MAX_UINTXX;
	  return(next);
}
int  GetLastNode(Node *NodePool,int item);
int  GetLastNode(Node *NodePool,int item)
{
	  int last;
	  last=((int)NodePool[item].last)&MAX_UINTXX;
	  return(last);
}
void  DelNextNode(Node *NodePool,int last);
void  DelNextNode(Node *NodePool,int last)
{
	  int item,next;
	  Node   *itemptr;
	  Node   *lastptr;
	  Node   *nextptr;

	  lastptr =&(NodePool[last]);
	  item =((int)lastptr->next)&MAX_UINTXX;
	  if(last == item)	 return;
	  itemptr =&(NodePool[item]);
	  next=((int)itemptr->next)&MAX_UINTXX;
	  nextptr =&(NodePool[next]);

	  lastptr->next=(uintxx)next;
	  nextptr->last=(uintxx)last;

	  itemptr->last=(uintxx)item;
	  itemptr->next=(uintxx)item;
	  itemptr->root=(uintxx)item;
}

void  DelLastNode(Node *NodePool,int next);
void  DelLastNode(Node *NodePool,int next)
{
	  int last,item;
	  Node   *itemptr;
	  Node   *lastptr;
	  Node   *nextptr;

	  nextptr =&(NodePool[next]);
	  item =((int)nextptr->last)&MAX_UINTXX;
	  if(next == item)	 return;
	  itemptr =&(NodePool[item]);
	  last=((int)itemptr->last)&MAX_UINTXX;
	  lastptr =&(NodePool[last]);

	  lastptr->next=(uintxx)next;
	  nextptr->last=(uintxx)last;

	  itemptr->last=(uintxx)item;
	  itemptr->next=(uintxx)item;
	  itemptr->root=(uintxx)item;

}

/*Make a Node Is a Root In Queue */
void  QueueNode(Node *NodePool,int item);
void  QueueNode(Node *NodePool,int item)
{
  Node   *itemptr;

  itemptr =&(NodePool[item]);
  itemptr->next=(uintxx)item;
  itemptr->last=(uintxx)item;
  itemptr->root=(uintxx)item;

}

/*------------------------------------*/
/*Put a Node after one Node*/
void  AppendNode(Node *NodePool,int last,int item);
void  AppendNode(Node *NodePool,int last,int item)
{
  int  next,root;
  Node   *lastptr;
  Node   *itemptr;
  Node   *nextptr;
  lastptr =&(NodePool[last]);
  root=((int)lastptr->root)&MAX_UINTXX;
  next=((int)lastptr->next)&MAX_UINTXX;
  lastptr->next=item;

  itemptr =&(NodePool[item]);
  itemptr->next=(uintxx)next;
  itemptr->last=(uintxx)last;
  itemptr->root=(uintxx)root;

  nextptr =&(NodePool[next]);
  nextptr->last=(uintxx)item;
}
/*------------------------------------*/
/*Put a Node Befor one Node*/
void  BeforeNode(Node *NodePool,int next,int item);
void  BeforeNode(Node *NodePool,int next,int item)
{
  int  last,root;
  Node   *nextptr;
  Node   *itemptr;
  Node   *lastptr;

  nextptr =&(NodePool[next]);
  root=((int)nextptr->root)&MAX_UINTXX;
  last=((int)nextptr->last)&MAX_UINTXX;
  nextptr->last=item;

  itemptr =&(NodePool[item]);
  itemptr->next=(uintxx)next;
  itemptr->last=(uintxx)last;
  itemptr->root=(uintxx)root;

  lastptr =&(NodePool[last]);
  lastptr->next=(uintxx)item;

}
/*------------------------------------*/
/*Delete a Node From Queue */
void  DeleteNode(Node *NodePool,int item);
void  DeleteNode(Node *NodePool,int item)
{
  int last,next;
  Node   *itemptr;
  Node   *lastptr;
  Node   *nextptr;

  itemptr =&(NodePool[item]);
  next=((int)itemptr->next)&MAX_UINTXX;
  if(next == item)	 return;
  last=((int)itemptr->last)&MAX_UINTXX;
  lastptr =&(NodePool[last]);
  nextptr =&(NodePool[next]);

  lastptr->next=(uintxx)next;
  nextptr->last=(uintxx)last;

  itemptr->last=(uintxx)item;
  itemptr->next=(uintxx)item;
  itemptr->root=(uintxx)item;
}
/*------------------------------------*/
/*Find a Node In A Queue */
int  LocateNode(Node *NodePool,int root,int item);
int  LocateNode(Node *NodePool,int root,int item)
{
  int next;
  next=((int)NodePool[root].next)&MAX_UINTXX;
  for(;;)
  {
    if(next == root)	break;	/*no find*/
	if(next == item)	break;	/*find the node*/
    next=((int)NodePool[next].next)&MAX_UINTXX;
  }
  return(next);
}


/*------------------------------------*/
/*Browse a Node In Queue */
int  BrowseNode(Node *NodePool,int root);
int  BrowseNode(Node *NodePool,int root)
{
  int next,size;
  size=1;
  next=((int)NodePool[root].next)&MAX_UINTXX;
  for(;;)
  {
    if(next == root) break;
    next=((int)NodePool[next].next)&MAX_UINTXX;
	size++;
  }
  return(size);
}

/*================================================================*/
/* end of node.c */
