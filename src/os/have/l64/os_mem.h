
/*------------------------------------
 * os_mem.h
 * Create:  2021-01-31
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
#if	_OS_HAVE_L64_
#ifndef OS_HAVE_L64_OS_MEM_H_
#define OS_HAVE_L64_OS_MEM_H_
/*================================================================*/
extern void os_memclr(void *src, int size);
extern void os_memcpy(void *src, void *dest, int size);
extern void *os_calloc(int cnt, int size);
extern void *os_malloc(int size);
extern void os_free(void *p);
/*================================================================*/
#endif
#endif 
/* end of os_mem.h */
