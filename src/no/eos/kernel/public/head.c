
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
int GetFirst(uintxx *head,int grp);
int GetFirst(uintxx *head,int grp)
{
	int ret;
	ret=(int)head[grp];
	ret &= MAX_UINTXX;
	return ret;
}

void SetFirst(uintxx *head,int grp,int pno);
void SetFirst(uintxx *head,int grp,int pno)
{
	head[grp]=(uintxx)pno;
}

/*------------------------------------*/

/*================================================================*/

/* end of head.c */
