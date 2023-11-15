
/*------------------------------------
 * rbl_rand.c
 * Create:  2023-02-21
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
#include <stdlib.h>
static int flag=0;
int rbl_get_rand(void);
int rbl_get_rand()
{
	int i;

	/* Intializes random number generator */
	if(flag==0)
	{
		srand(200);
		flag=1;
	}

	i = rand();
	return i;
}

/*================================================================*/

/* end of rbl_rand.c */
