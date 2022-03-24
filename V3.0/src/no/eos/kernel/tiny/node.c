
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
#if	EOS_TINY_MODE
#include "node.h"
/*================================================================*/
/*Make a Node Is a Root In Queue */
void  QueueNode(Node *NodePool,int item);
void  QueueNode(Node *NodePool,int item)
{
  Node   *itemptr;

  itemptr =&(NodePool[item]);
  itemptr->next=(unsigned char)item;
  itemptr->last=(unsigned char)item;
  itemptr->root=(unsigned char)item;

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
  root=((int)lastptr->root)&0xff;
  next=((int)lastptr->next)&0xff;
  lastptr->next=item;

  itemptr =&(NodePool[item]);
  itemptr->next=(unsigned char)next;
  itemptr->last=(unsigned char)last;
  itemptr->root=(unsigned char)root;

  nextptr =&(NodePool[next]);
  nextptr->last=(unsigned char)item;
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
  root=((int)nextptr->root)&0xff;
  last=((int)nextptr->last)&0xff;
  nextptr->last=item;

  itemptr =&(NodePool[item]);
  itemptr->next=(unsigned char)next;
  itemptr->last=(unsigned char)last;
  itemptr->root=(unsigned char)root;

  lastptr =&(NodePool[last]);
  lastptr->next=(unsigned char)item;

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
  next=((int)itemptr->next)&0xff;
  if(next == item)	 return;
  last=itemptr->last;
  itemptr->last=(unsigned char)item;
  next=((int)itemptr->next)&0xff;
  itemptr->next=(unsigned char)item;
  itemptr->root=(unsigned char)item;

  lastptr =&(NodePool[last]);
  lastptr->next=(unsigned char)next;

  nextptr =&(NodePool[next]);
  nextptr->last=(unsigned char)last;

}
/*------------------------------------*/
/*Find a Node In A Queue */
int  LocateNode(Node *NodePool,int root,int item);
int  LocateNode(Node *NodePool,int root,int item)
{
  int next;
  next=((int)NodePool[root].next)&0xff;
  for(;;)
  {
    if(next == root)	break;	/*no find*/
	if(next == item)	break;	/*find the node*/
    next=((int)NodePool[next].next)&0xff;
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
  next=((int)NodePool[root].next)&0xff;
  for(;;)
  {
    if(next == root) break;
    next=((int)NodePool[next].next)&0xff;
	size++;
  }
  return(size);
}

/*================================================================*/
#endif
/* end of node.c */
