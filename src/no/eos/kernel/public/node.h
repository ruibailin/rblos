
/*------------------------------------
 * node.h
 * Create:  2023-02-17
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */
#ifndef SRC_KERNEL_PUBLIC_NODE_H_
#define SRC_KERNEL_PUBLIC_NODE_H_

#include "1imp.h"
/*================================================================*/
/*define Node used in list*/
typedef struct{
	uintxx		last;
	uintxx		next;
	uintxx		root;		//For debug
	uintxx		dumb;		//32 bits
} Node;

extern int  GetNextNode(Node *NodePool,int last);
extern void  DelNextNode(Node *NodePool,int last);
extern int  GetLastNode(Node *NodePool,int next);
extern void  DelLastNode(Node *NodePool,int next);

extern void  QueueNode(Node *NodePool,int item);
extern void  AppendNode(Node *NodePool,int last,int item);
extern void  BeforeNode(Node *NodePool,int next,int item);
extern void  DeleteNode(Node *NodePool,int item);
extern int  LocateNode(Node *NodePool,int root,int item);
extern int  BrowseNode(Node *NodePool,int root);
/*================================================================*/


#endif /* SRC_KERNEL_PUBLIC_NODE_H_ */
