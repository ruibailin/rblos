
/*------------------------------------
 * rbl_memory.c
 * Create:  2023-02-18
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
#include <string.h>

void rbl_memclr(void *src, int size);
void rbl_memclr(void *src, int size)
{
	memset(src,0,size);
}

void rbl_memcpy(void *src, void *dest, int size);
void rbl_memcpy(void *src, void *dest, int size)
{
	memcpy(src,dest,size);
}

/*================================================================*/
#include <stdlib.h>
void *rbl_calloc(int cnt, int size);
void *rbl_calloc(int cnt, int size)
{
	void *p;
	p=calloc(cnt,size);
	return p;
}

void *rbl_malloc(int size);
void *rbl_malloc(int size)
{
	void *p;
	p=malloc(size);
	return p;
}

void rbl_free(void *p);
void rbl_free(void *p)
{
	if(p==NULL)
		return;
	free(p);
}

/*================================================================*/

/* end of rbl_memory.c */
