
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

#include	"0ctr.h"
#if	EOS_SMALL_MODE
#include "node.h"
/*================================================================*/
/*Make a Node Is a Root In Queue */
void  QueueNode(Node *NodePool,int item);
void  QueueNode(Node *NodePool,int item)
{
  Node   *itemptr;

  itemptr =&(NodePool[item]);
  itemptr->next=(unsigned short)item;
  itemptr->last=(unsigned short)item;
  itemptr->root=(unsigned short)item;

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
  root=((int)lastptr->root)&0xffff;
  next=((int)lastptr->next)&0xffff;
  lastptr->next=item;

  itemptr =&(NodePool[item]);
  itemptr->next=(unsigned short)next;
  itemptr->last=(unsigned short)last;
  itemptr->root=(unsigned short)root;

  nextptr =&(NodePool[next]);
  nextptr->last=(unsigned short)item;
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
  root=((int)nextptr->root)&0xffff;
  last=((int)nextptr->last)&0xffff;
  nextptr->last=item;

  itemptr =&(NodePool[item]);
  itemptr->next=(unsigned short)next;
  itemptr->last=(unsigned short)last;
  itemptr->root=(unsigned short)root;

  lastptr =&(NodePool[last]);
  lastptr->next=(unsigned short)item;

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
  next=((int)itemptr->next)&0xffff;
  if(next == item)	 return;
  last=itemptr->last;
  itemptr->last=(unsigned short)item;
  next=((int)itemptr->next)&0xffff;
  itemptr->next=(unsigned short)item;
  itemptr->root=(unsigned short)item;

  lastptr =&(NodePool[last]);
  lastptr->next=(unsigned short)next;

  nextptr =&(NodePool[next]);
  nextptr->last=(unsigned short)last;

}
/*------------------------------------*/
/*Find a Node In A Queue */
int  LocateNode(Node *NodePool,int root,int item);
int  LocateNode(Node *NodePool,int root,int item)
{
  int next;
  next=((int)NodePool[root].next)&0xffff;
  for(;;)
  {
    if(next == root)	break;	/*no find*/
	if(next == item)	break;	/*find the node*/
    next=((int)NodePool[next].next)&0xffff;
  }
  return(next);
}


/*------------------------------------*/
/*Browse a Node In Queue */
int  BrowseNode(Node *NodePool,int root);
int  BrowseNode(Node *NodePool,int root)
{
  int next,size;
  size=0;
  next=((int)NodePool[root].next)&0xffff;
  for(;;)
  {
    if(next == root) break;
    next=((int)NodePool[next].next)&0xffff;
	size++;
  }
  return(size);
}

/*================================================================*/
#endif
/* end of node.c */
