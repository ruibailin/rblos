
/*------------------------------------
 * snode.h
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
#ifndef SRC_KERNEL_PUBLIC_SNODE_H_
#define SRC_KERNEL_PUBLIC_SNODE_H_
#include "1imp.h"
/*================================================================*/
/*define Node used in list*/
typedef struct{
	uintxx		next;
	uintxx		root;		//for debug
} SNode;

extern int  GetNextSNode(SNode *NodePool,int item);
extern int  GetLastSNode(SNode *NodePool,int item);
extern int  DelNextSNode(SNode *NodePool,int last);

extern void  QueueSNode(SNode *NodePool,int item);
extern void  AppendSNode(SNode *NodePool,int last,int item);
extern int  LocateSNode(SNode *NodePool,int head,int item);
extern int  BrowseSNode(SNode *NodePool,int head);
extern void  DeleteSNode(SNode *NodePool,int item);
/*================================================================*/
#endif /* SRC_KERNEL_PUBLIC_SNODE_H_ */
