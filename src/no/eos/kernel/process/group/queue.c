
/*------------------------------------
 * queue.c
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

#include "1imp.h"
#include "head.h"
/*================================================================*/
static 	SNode node_pool[PAT_NODE_NUM];
static int grp_num[MAX_TYPE_NUM];
/*================================================================*/
void 	grp_ini_pro(void);
void 	grp_ini_pro()
{
	int i;
	for(i=0;i<MAX_PAT_NUM;i++)
	{
		QueueSNode(node_pool,i);
	}

	for(i=0;i<MAX_TYPE_NUM;i++)
	{
		grp_num[i]=0;
	}
	grp_ini_head();
}

int 	grp_get_pro(int pro);
int 	grp_get_pro(int pro)
{
	int pno;
	if(pro>PAT_NODE_NUM-1)
		return 0;
	pno=GetNextSNode(node_pool,pro);
	return pno;
}

void 	grp_add_pro(int last,int pro);
void 	grp_add_pro(int last,int pro)
{
	if(last>PAT_NODE_NUM-1)
		return;
	if(pro>PAT_NODE_NUM-1)
		return;
	if(pro==0)
		return;
	AppendSNode(node_pool,last,pro);
}

void 	grp_del_pro(int pro);
void 	grp_del_pro(int pro)
{
	if(pro>PAT_NODE_NUM-1)
		return;
	if(pro==0)
		return;
	DeleteSNode(node_pool,pro);
}

/*------------------------------------*/
int 	grp_get_next_pro(int grp,int pro);
int 	grp_get_next_pro(int grp,int pro)
{
	int pno;
	if(grp>MAX_TYPE_NUM-1)
		return 0;
	if(pro>PAT_NODE_NUM-1)
		return 0;
	pno=grp_get_head(grp);
	if(pno==0)
		return 0;
	if(pro==0)			//if 0, get next of head;
		pro=pno;
	pno=GetNextSNode(node_pool,pro);
	return pno;
}

void 	grp_add_next_pro(int grp,int pro);
void 	grp_add_next_pro(int grp,int pro)
{
	int pno;
	if(grp>MAX_TYPE_NUM-1)
		return;
	if(pro>PAT_NODE_NUM-1)
		return;
	if(pro==0)
		return;
	pno=grp_get_head(grp);
	if(pno==0)
	{
		grp_set_head(grp,pro);
	}
	else
	{
		AppendSNode(node_pool,pno,pro);
	}
	grp_num[grp]++;
}

void 	grp_del_next_pro(int grp,int pro);
void 	grp_del_next_pro(int grp,int pro)
{
	int pno;
	if(grp>MAX_TYPE_NUM-1)
		return;
	if(pro>PAT_NODE_NUM-1)
		return;
	if(pro==0)
		return;
	pno=grp_get_head(grp);
	if(pno==0)
		return;
	if(pno==pro)
	{
		grp_set_head(grp,0);		//delete first node;
	}
	else
	{
		DeleteSNode(node_pool,pro);
	}
	grp_num[grp]--;
}
/*------------------------------------*/
int 	grp_get_num(int grp);
int 	grp_get_num(int grp)
{
	if(grp>MAX_TYPE_NUM-1)
		return 0;
	return grp_num[grp];
}

void 	grp_inc_num(int grp);
void	grp_inc_num(int grp)
{
	if(grp>MAX_TYPE_NUM-1)
		return;
	grp_num[grp]++;
}

void 	grp_dec_num(int grp);
void	grp_dec_num(int grp)
{
	if(grp>MAX_TYPE_NUM-1)
		return;
	grp_num[grp]--;
}
/*================================================================*/

/* end of queue.c */
