
/*------------------------------------
 * process1.c
 * Create:  2023-02-19
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 * System process to create timer for all user process
 *
 *
 *
 *------------------------------------
 */

#include "1imp.h"

/*================================================================*/
#include "r_tcb.h"
void	sys_timer(void *in);
void	sys_timer(void *in)
{
	run_tcb_l10ms();
	run_tcb_10ms();
	run_tcb_100ms();
	run_tcb_1s();
}

/*================================================================*/

/* end of process1.c */
