
/*------------------------------------
 * process02.c
 * Create:  2023-02-19
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 * System Idle Process to calculate CPU Ocuprency rate and defrage memory
 *
 *
 *
 *------------------------------------
 */

#include "1imp.h"

/*================================================================*/
extern void soc_clr_wdt(void);
void	sys_idler(void *in);
void	sys_idler(void *in)
{
	soc_clr_wdt();
}

/*================================================================*/

/* end of system2.c */
