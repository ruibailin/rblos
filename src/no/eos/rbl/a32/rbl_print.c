
/*------------------------------------
 * rbl_print.c
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
#include <stdio.h>
#include <stdlib.h>
void rbl_puts(const char *s);
void rbl_puts(const char *s)
{
	puts(s);
}

void rbl_printf(const char *fmt, ...);
void rbl_printf(const char *fmt, ...)
{
	printf(fmt);
}


/*================================================================*/

/* end of rbl_print.c */
