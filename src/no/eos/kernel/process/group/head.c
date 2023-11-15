
/*------------------------------------
 * head.c
 * Create:  2023-05-18
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

/*================================================================*/
static uintxx grp_head[MAX_TYPE_NUM];
/*------------------------------------*/
void 	grp_ini_head(void);
void 	grp_ini_head()
{
	int i;
	for(i=0;i<MAX_TYPE_NUM;i++)
	{
		grp_head[i]=0;
	}
}

int grp_get_head(int grp);
int grp_get_head(int grp)
{
	int ret;
	ret=(int)grp_head[grp];
	ret &= MAX_UINTXX;
	return ret;
}

void grp_set_head(int grp,int pno);
void grp_set_head(int grp,int pno)
{
	grp_head[grp]=(uintxx)pno;
}

/*================================================================*/

/* end of head.c */
