/*
 * print.c
 *
 *  Created on: Nov 6, 2023
 *      Author: stever
 */


/*================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
/*------------------------------------*/
//Since we can't print in interrupt context
static char pp_buf[128];
void knl_print(const char *fmt, ...)   _ATTRIBUTE ((__format__ (__printf__, 1, 2)));
void knl_print(const char *fmt, ...)
{
	if(pp_buf[0]!='\0')		//don't overwrite
	return;
    va_list ap;
    va_start(ap,fmt);
    vsnprintf(pp_buf,120,fmt,ap);
    va_end(ap);
}
/*------------------------------------*/
#include "../1imp.h"
void usr_print(void);
void usr_print()
{
	if(pp_buf[0]=='\0')
	return;
	eos_print("%s",pp_buf);
	pp_buf[0]='\0';
}
/*================================================================*/
/* end of print.c */
