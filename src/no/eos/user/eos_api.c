
/*------------------------------------
 * eos_api.c
 * Create:  2023-02-24
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */

#include "eos_api.h"
/*================================================================*/

/*------------------------------------*/
void eos_set_timer(int length);
void eos_set_timer(int length)
{
	EOS_SET(0,length);			//user timer0 as default timer
}

void eos_reset_timer(void);
void eos_reset_timer()
{
	EOS_KILL(0);			//user timer0 as default timer
}
/*================================================================*/
/* end of eos_api.c */
