
/*------------------------------------
 * r_delay.c
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
#include "r_time.h"
void os_delay_us(int us);
void os_delay_us(int us)
{
	long int l,t;
	int delay;
	l=os_get_us();
	for(;;)
	{
		t=os_get_us();
		delay=(int)(t-l);
		if(delay<=0)
			break;
		if(delay<us)
			continue;
		else
			break;
	}
}

void os_delay_ms(int ms);
void os_delay_ms(int ms)
{
	long int l,t;
	int delay;
	l=os_get_ms();
	for(;;)
	{
		t=os_get_ms();
		delay=(int)(t-l);
		if(delay<=0)
			break;
		if(delay<ms)
			continue;
		else
			break;
	}
}

/*================================================================*/
#endif
/* end of r_delay.c */
