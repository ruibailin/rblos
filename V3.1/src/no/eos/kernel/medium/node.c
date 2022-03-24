
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
#if	EOS_MEDIUM_MODE
#include "node.h"
/*================================================================*/
/*Make a Node Is a Root In Queue */
void  QueueNode(Node *NodePool,int item);
void  QueueNode(Node *NodePool,int item)
{
  Node   *itemptr;

  itemptr =&(NodePool[item]);
  itemptr->next=item;
  itemptr->last=item;
  itemptr->root=item;

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
void  BeforeNode(Node *NodePool,int next,int item);
void  BeforeNode(Node *NodePool,int next,int item)
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
  next=itemptr->next;
  if(next == item)	 return;
  last=itemptr->last;
  itemptr->last=(unsigned short)item;
  next=itemptr->next;
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
  next=NodePool[root].next;
  for(;;)
  {
    if(next == root)	break;	/*no find*/
	if(next == item)	break;	/*find the node*/
    next=NodePool[next].next;
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
  next=NodePool[root].next;
  for(;;)
  {
    if(next == root) break;
    next=NodePool[next].next;
	size++;
  }
  return(size);
}

/*================================================================*/
#endif
/* end of node.c */
