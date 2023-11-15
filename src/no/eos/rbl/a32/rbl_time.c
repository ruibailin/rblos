/*
 * rbl_time.c
 *
 *  Created on: Mar 2, 2023
 *      Author: stever
 */


#include "1imp.h"
/*================================================================*/
#include <time.h>
//#include "stm32l4xx_hal.h"

#if defined ( __GNUC__ )
#ifndef __weak
#define __weak __attribute__((weak))
#endif
#endif

__weak time_t LOCAL_Get_Current_Epoch_Time(void);
__weak time_t LOCAL_Get_Current_Epoch_Time()
{
	time_t temp;
	temp=0;
	return temp;
}
/*------------------------------------*/
extern uint32_t HAL_GetTick(void);
int rbl_get_usec(void);
int rbl_get_usec(void)
{
	uint32_t runtime;
	runtime = HAL_GetTick();
	runtime %= 1000;
	runtime *= 1000;		//in order to be complied with other OS
	return runtime;
}
/*------------------------------------*/
int rbl_get_sec(void);
int rbl_get_sec()
{
	time_t now;
	struct tm curtime;
	now=LOCAL_Get_Current_Epoch_Time();
	localtime_r(&now, &curtime);
	return(curtime.tm_sec);
}

int rbl_get_second(void);
int rbl_get_second()
{
	time_t now;
	struct tm curtime;
	now=LOCAL_Get_Current_Epoch_Time();
	localtime_r(&now, &curtime);
	return(curtime.tm_sec);
}
int rbl_get_minute(void);
int rbl_get_minute()
{
	time_t now;
	struct tm curtime;
	now=LOCAL_Get_Current_Epoch_Time();
	localtime_r(&now, &curtime);
	return(curtime.tm_min);
}

int rbl_get_hour(void);
int rbl_get_hour()
{
	time_t now;
	struct tm curtime;
	now=LOCAL_Get_Current_Epoch_Time();
	localtime_r(&now, &curtime);
    return(curtime.tm_hour);
}

int rbl_get_mday(void);
int rbl_get_mday()
{
	time_t now;
	struct tm curtime;
	now=LOCAL_Get_Current_Epoch_Time();
	localtime_r(&now, &curtime);
	return(curtime.tm_mday);
}

int rbl_get_month(void);
int rbl_get_month()
{
	time_t now;
	struct tm curtime;
	now=LOCAL_Get_Current_Epoch_Time();
	localtime_r(&now, &curtime);
	return(curtime.tm_mon);
}

int rbl_get_year(void);
int rbl_get_year()
{
	time_t now;
	struct tm curtime;
	now=LOCAL_Get_Current_Epoch_Time();
	localtime_r(&now, &curtime);
	return(curtime.tm_year);
}

int rbl_get_wday(void);
int rbl_get_wday()
{
	time_t now;
	struct tm curtime;
	now=LOCAL_Get_Current_Epoch_Time();
	localtime_r(&now, &curtime);
	return(curtime.tm_wday);
}

/*================================================================*/
/* end of rbl_time.c */
