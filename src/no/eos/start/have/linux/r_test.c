
/*------------------------------------
 * r_test.c
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
#ifdef TEST_IN_LINUX
/*================================================================*/
/*================================================================*/
#include "../../../eos.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

extern	int		EOS_SELF(void);
#define SELF EOS_SELF
extern	int		EOS_STATE(void);
#define STATE EOS_STATE
extern	void	EOS_NEXT(int state);
#define NEXT_STATE EOS_NEXT
extern	int		EOS_EVENT(void);
#define EVENT EOS_EVENT
extern	int		EOS_LENGTH(void);
#define LENGTH EOS_LENGTH
extern	int		EOS_SENDER(void);
#define SENDER EOS_SENDER
extern	void	EOS_ASEND(int dest,int event,int len,void *in);
#define ASEND EOS_ASEND
extern	void	EOS_SET(int ptno,int len);
extern  void eos_set_timer(int length);
#define SET EOS_SET
extern	void	EOS_KILL(int ptno);
extern  void eos_reset_timer(void);
#define KILL EOS_KILL

extern void app_clt_init_skt(void);
extern void app_clt_free_skt(void);
extern int app_clt_send_skt(char *frm,int size);
extern int app_clt_recv_skt(char *frm,int size);

static char ac[]={0x41,0x43,0xF1,0x80,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0xE9,0x5D,0x00};
static char rec[480];
/*------------------------------------*/
void real_pro10(void *ptr);
void real_pro10(void *ptr)
{
	int ii;
	int ss,ee,pno;
	int ret;
	ss=STATE();
	pno=SELF();
	ee=EVENT();

	switch(ss)
	{
	case 0:
		ii=60;
		SET(1,ii*10);
		printf(" proc %d set timer %d \n",pno,ii);
		app_clt_init_skt();
		NEXT_STATE(1);
		break;
	case 1:
		ii=60;
		SET(1,ii*10);
//		printf(" proc %d set timer %d \n",pno,ii);
		ret=app_clt_send_skt(ac,13);
		if(ret!=13)
			printf(" Wrong send \r\n");
		ret=app_clt_recv_skt(rec,40);
		printf(" Recv %d \r\n",ret);
		ASEND(20,ii+10,0,(void *)0L);
		break;
	default:
		break;
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
			printf(" proc %d event %d,timer interval %d\n",pno,ee,ii);
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
  int xx;
  time_t timep;
  struct tm *p;

  xx=STATE();
  SET(1,1000);
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
#include "../../../kernel/process/basic/r_pat.h"
void	ini_def_proc(void);
void	ini_def_proc()
{
	set_pat_entry(1,&real_pro10);
	set_pat_entry(2,&real_pro20);
	set_pat_entry(3,&watch_dog);
}


/*================================================================*/
#else
void ini_def_proc(void);
void ini_def_proc()
{

}
#endif
/* end of r_test.c */
