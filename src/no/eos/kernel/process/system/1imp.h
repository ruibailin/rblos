
/*------------------------------------
 * 1imp.h
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

#ifndef KERNEL_PROC_SYSTEM_1IMP_H_
#define KERNEL_PROC_SYSTEM_1IMP_H_

/*================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
/*------------------------------------*/
#include "../1imp.h"
#include "../../1imp.h"

extern void knl_print(const char *fmt, ...)   _ATTRIBUTE ((__format__ (__printf__, 1, 2)));
extern void usr_print(void);


/*================================================================*/

#endif 
/* end of 1imp.h */
