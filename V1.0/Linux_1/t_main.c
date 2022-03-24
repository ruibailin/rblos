#include "r_msg.h"
#include "r_tcb.h"
#include "r_pat.h"
#include "r_pcb.h"
#include "r_func.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

/*------------------------------------*/
void real_pro10(void *ptr);
void real_pro10(void *ptr)
{
	int ii;
	int  ss,ee,pno;
	ss=STATE();
	pno=SELF();
	ee=EVENT();

//	printf(" proc %d event %d \n",pno,ee);
	if(ss ==0)
	{
		ii=60;
		SET(1,ii);
//		printf(" proc %d set timer %d \n",pno,ii);
		NEXT_STATE(1);
	}
	else
	{
		ii=60;
		SET(1,ii);
//		printf(" proc %d set timer %d \n",pno,ii);
		ASEND(20,ii+10,0,(void *)0L);
	}
}



/*================================================================*/
static	short int	last_ms;
static	short int	this_ms;
/*----------------------------------------*/
static	short int	get_ms(void);
static	short int	get_ms()
{
	short int	ms;
    struct timeval    tv;
    struct timezone	  tz;
	gettimeofday(&tv, &tz);
	ms=(short int)(tv.tv_usec/1000);
	return(ms);
}
/*------------------------------------*/
void real_pro20(void *ptr);
void real_pro20(void *ptr)
{
	int  ss,ee,pno;
	short int ii;
	ss=STATE();
	if(ss==0) 
	{
		last_ms=get_ms();
		NEXT_STATE(1);
	}
	else
	{
		pno=SELF();
		ee=EVENT();
		this_ms=get_ms();
		if(this_ms > last_ms)
			ii=this_ms-last_ms;
		else
			ii=1000-last_ms+this_ms;
		if(ii>604)
			printf(" wrong %d \n",ii);
		else
//			printf(" proc %d event %d,timer interval %d\n",pno,ee,ii);
		last_ms=this_ms;
	}
}
/*------------------------------------*/

static  unsigned int second=0;
static  unsigned int minute=0;
static  unsigned int hour=0;
void  watch_dog(void *ptr);
void  watch_dog(void *ptr)
{
  int xx,yy;
  time_t timep;
  struct tm *p;

  xx=STATE();
  SET(1,100);
  if(xx==0)
  {
	  time(&timep);
	  p=gmtime(&timep);
	  second=p->tm_sec;
	  minute=p->tm_min;
	  hour=p->tm_hour;
	  NEXT_STATE(1);
	return;
  }
  second++;
  if(second == 60)
  { second=0;minute++;}
  if(minute == 60)
  { minute=0; hour++;}
  if(hour == 24)
  hour=0;

  printf("%2d:%02d:%02d \n",hour,minute,second);

}
/*------------------------------------*/
void	ini_test_proc(void);
void	ini_test_proc()
{
	set_pat_entry(10,&real_pro10);
	set_pat_entry(20,&real_pro20);
	set_pat_entry(21,&watch_dog);
}

