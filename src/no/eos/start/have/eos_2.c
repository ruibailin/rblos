
/*------------------------------------
 * eos.c
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
#if	EOS_WITH_OS
/*================================================================*/
#include "1imp.h"
#include "r_time.h"
#include "r_sleep.h"
#include "r_delay.h"
#define EOS_SCH_CYCLE 1000
static long int last_us=0;
static long int this_us=0;
int cal_cpu_rate(void);
int cal_cpu_rate()
{
	int busy;
	int idle;
	float rate;
	this_us=os_get_us();
	busy=(int)(this_us-last_us);
	if(busy>EOS_SCH_CYCLE)
	{
		os_printf("Too Busy! %d\n",busy);
		last_us=os_get_us();
		return 100;
	}
	rate = busy/(EOS_SCH_CYCLE);
	rate *= 100;
	idle=EOS_SCH_CYCLE-busy;
//	os_sleep_us(idle);
	os_delay_us(idle*10);
	last_us=os_get_us();
//	eos_time();
	return((int)rate);
}

/*================================================================*/
#endif
/* end of eos.c */
