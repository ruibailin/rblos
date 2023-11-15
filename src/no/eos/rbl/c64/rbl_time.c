/*
 * rbl_time.c
 *
 *  Created on: Mar 2, 2023
 *      Author: stever
 */


#include "1imp.h"
/*================================================================*/
#include <time.h>
#include <sys/time.h>
/*------------------------------------*/
int rbl_get_usec(void);
int rbl_get_usec(void)
{
	uint32_t runtime;
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	runtime = current_time.tv_usec;
	return runtime;
}
/*------------------------------------*/
int rbl_get_sec(void);
int rbl_get_sec()
{
	time_t now;
	struct tm curtime;
	localtime_r(&now, &curtime);
	return(curtime.tm_sec);
}

int rbl_get_second(void);
int rbl_get_second()
{
	time_t now;
	struct tm curtime;
	localtime_r(&now, &curtime);
	return(curtime.tm_sec);
}
int rbl_get_minute(void);
int rbl_get_minute()
{
	time_t now;
	struct tm curtime;
	localtime_r(&now, &curtime);
	return(curtime.tm_min);
}

int rbl_get_hour(void);
int rbl_get_hour()
{
	time_t now;
	struct tm curtime;
	localtime_r(&now, &curtime);
    return(curtime.tm_hour);
}

int rbl_get_mday(void);
int rbl_get_mday()
{
	time_t now;
	struct tm curtime;
	localtime_r(&now, &curtime);
	return(curtime.tm_mday);
}

int rbl_get_month(void);
int rbl_get_month()
{
	time_t now;
	struct tm curtime;
	localtime_r(&now, &curtime);
	return(curtime.tm_mon);
}

int rbl_get_year(void);
int rbl_get_year()
{
	time_t now;
	struct tm curtime;
	localtime_r(&now, &curtime);
	return(curtime.tm_year);
}

int rbl_get_wday(void);
int rbl_get_wday()
{
	time_t now;
	struct tm curtime;
	localtime_r(&now, &curtime);
	return(curtime.tm_wday);
}

/*================================================================*/
/* end of rbl_time.c */
