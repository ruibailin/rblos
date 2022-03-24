
/*------------------------------------
 * r_sleep.c
 * Create:  2021-10-19
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
#if	EOS_IN_LINUX
/*================================================================*/
#include <unistd.h>
void os_sleep_us(int us);
void os_sleep_us(int us)
{
	usleep(us);
}

void os_sleep_ms(int ms);
void os_sleep_ms(int ms)
{
	usleep(ms*1000);
}

void os_sleep_s(int s);
void os_sleep_s(int s)
{
	sleep(s);
}

/*================================================================*/
#endif
/* end of r_sleep.c */
