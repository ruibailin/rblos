
/*------------------------------------
 * node.h
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
#if	EOS_MEDIUM_MODE
#ifndef EOS_KERNEL_MEDIUM_NODE_H_
#define EOS_KERNEL_MEDIUM_NODE_H_
/*================================================================*/
/*define Node used in list*/
typedef struct{
	int		last;
	int		next;
	int		root;
} Node;

void  QueueNode(Node *NodePool,int item);
void  AppendNode(Node *NodePool,int last,int item);
void  BeforeNode(Node *NodePool,int next,int item);
void  DeleteNode(Node *NodePool,int item);
int  LocateNode(Node *NodePool,int root,int item);
int  BrowseNode(Node *NodePool,int root);
/*================================================================*/
#endif
#endif
/* end of node.h */
