
/*------------------------------------
 * snode.c
 * Create:  2023-02-17
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 * Single way SNode
 * Used in one-way link
 *
 *
 *------------------------------------
 */

#include "snode.h"

/*================================================================*/
int  GetNextSNode(SNode *NodePool,int item);
int  GetNextSNode(SNode *NodePool,int item)
{
  int next;
  next=((int)NodePool[item].next)&MAX_UINTXX;
  return(next);
}
/*------------------------------------*/
/*Get a Last SNode In Queue */
int  GetLastSNode(SNode *NodePool,int item);
int  GetLastSNode(SNode *NodePool,int item)
{
  int next,last;

  next=GetNextSNode(NodePool,item);
  last=next;
  for(;;)
  {
    if(next == item) break;
    last=next;
    next=GetNextSNode(NodePool,next);
  }
  return(last);
}

/*------------------------------------*/
/*Delete a SNode item behind of SNode last From Queue */
int  DelNextSNode(SNode *NodePool,int last);
int  DelNextSNode(SNode *NodePool,int last)
{
  int next,item;
  SNode   *itemptr;
  SNode   *lastptr;

  lastptr =&(NodePool[last]);
  item=((int)lastptr->next)&MAX_UINTXX;
  if(item == last)	 return item;		//head of a queue

  itemptr =&(NodePool[item]);
  next=((int)itemptr->next)&MAX_UINTXX;
  lastptr->next=(uintxx)next;

  itemptr->next=item;
  itemptr->root=item;
  return item;
}

/*------------------------------------*/
/*Make a SNode Is a Root In Queue */
void  QueueSNode(SNode *NodePool,int item);
void  QueueSNode(SNode *NodePool,int item)
{
  SNode   *itemptr;

  itemptr =&(NodePool[item]);
  itemptr->next=(uintxx)item;
  itemptr->root=(uintxx)item;
}
/*------------------------------------*/
/*Put a SNode item after one SNode last*/
void  AppendSNode(SNode *NodePool,int last,int item);
void  AppendSNode(SNode *NodePool,int last,int item)
{
  int  next,root;
  SNode   *lastptr;
  SNode   *itemptr;
  lastptr =&(NodePool[last]);
  root=((int)lastptr->root)&MAX_UINTXX;
  next=((int)lastptr->next)&MAX_UINTXX;
  lastptr->next=item;

  itemptr =&(NodePool[item]);
  itemptr->next=(uintxx)next;
  itemptr->root=(uintxx)root;
}
/*------------------------------------*/
/*Find a Node In A Queue */
int  LocateSNode(SNode *NodePool,int root,int item);
int  LocateSNode(SNode *NodePool,int root,int item)
{
  int next;
  next=GetNextSNode(NodePool,root);
  for(;;)
  {
    if(next == root)	break;	/*no find*/
	if(next == item)	break;	/*find the node*/
    next=GetNextSNode(NodePool,next);
  }
  return(next);
}
/*------------------------------------*/
/*Browse a SNode In Queue */
int  BrowseSNode(SNode *NodePool,int root);
int  BrowseSNode(SNode *NodePool,int root)
{
  int next,size;
  size=1;
  next=GetNextSNode(NodePool,root);
  for(;;)
  {
    if(next == root) break;
    next=GetNextSNode(NodePool,next);
	size++;
  }
  return(size);
}
/*------------------------------------*/
/*Delete a SNode item behind of SNode last From Queue */
void  DeleteSNode(SNode *NodePool,int item);
void  DeleteSNode(SNode *NodePool,int item)
{
  int last;
  last = GetLastSNode(NodePool,item);
  DelNextSNode(NodePool,last);
}
/*================================================================*/

/* end of snode.c */
