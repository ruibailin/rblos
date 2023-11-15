
/*------------------------------------
 * r_time.c
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
#include <time.h>
#include <sys/time.h>

/*================================================================*/
long int	os_get_ms(void);
long int	os_get_ms()
{
	int	ms;
    struct timeval    tv;
    struct timezone	  tz;
	gettimeofday(&tv, &tz);
	ms=(int)(tv.tv_usec/1000);
	return(ms);
}

long int	os_get_us(void);
long int	os_get_us()
{
	long int	us;
    struct timeval    tv;
    struct timezone	  tz;
	gettimeofday(&tv, &tz);
	us=(long int)(tv.tv_usec);
	return(us);
}
/*================================================================*/
#endif
/* end of r_time.c */
