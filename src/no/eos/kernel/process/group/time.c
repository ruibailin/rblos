
/*------------------------------------
 * time.c
 * Create:  2023-02-17
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */

#include "1imp.h"
#include "queue.h"
/*================================================================*/
//static	int time_head=0;

static uintxx time_slot[PAT_NODE_NUM];		//TIME proc only run in its slot;
static	void set_time_slot(int pno);
static	void set_time_slot(int pno)			//not strictly good algorithm
{
	int slot,timer;
	timer=get_pat_attr(pno);
	if(timer==0)
		timer=1;
	slot=grp_get_num(TIME_PROC);
	slot += timer;
	slot %= timer;
	time_slot[pno]=slot;
}

void grp_add_time_pro(int pno);
void grp_add_time_pro(int pno)
{
	int time_head;
	time_head=grp_get_head(TIME_PROC);
	if(pno == time_head)
		return;
	grp_inc_num(TIME_PROC);
	if(time_head == 0)
		grp_set_head(TIME_PROC,pno);			//first process
	else
		grp_add_pro(time_head,pno);
	set_time_slot(pno);
}

void grp_del_time_pro(int pno);
void grp_del_time_pro(int pno)
{
	int time_head;
	time_head=grp_get_head(TIME_PROC);
	grp_dec_num(TIME_PROC);
	if(pno == time_head)
	{
		grp_set_head(TIME_PROC,0);
		return;
	}
	grp_del_pro(pno);
}

/*================================================================*/
#define SCHEDULE_TIME	1000

static int time_delta;
static int this_us,last_us;
extern int rbl_get_usec(void);

void grp_ini_time_pro(void);
void grp_ini_time_pro()
{
	int i,j;
	for(i=2;i<MAX_PAT_NUM;i++)
	{
		j=get_pat_tno(i);
		if(j==TIME_PROC)
		{
			grp_add_time_pro(i);
		}
	}
	time_delta=SCHEDULE_TIME;
	this_us=rbl_get_usec();
	last_us=this_us;
}


static	int is_time_run();
static	int is_time_run()
{
	int pass_us,error;

	this_us = rbl_get_usec();
	if(this_us<last_us)
		pass_us =(int)(this_us+1000000-last_us);
	else
		pass_us =(int)(this_us-last_us);

	if(pass_us<time_delta)
		return 0;
	last_us=this_us;
	error=pass_us-SCHEDULE_TIME;
	time_delta = time_delta -error;
	return 1;
}

long int knl_run_ms=0;

static int is_time_run_pro(int pno)
{
	int state;
	int slot;
	int attr;
	state=time_slot[pno];
	slot=(int)knl_run_ms;
	attr = get_pat_attr(pno);
	if(attr==0)
		attr=1;
	slot %= attr;
	if(slot == state)
		return 1;
	else
		return 0;
}
int	grp_run_time_pro(void);
int	grp_run_time_pro()
{
	int run;
	int pno;
	int time_head;
	time_head=grp_get_head(TIME_PROC);
	run=is_time_run();
	if(run==0)
		return 0;
	knl_run_ms++;
	run_pat_entry(1,0x0L);		//system_timer
	if(time_head == 0)
		return 0;				//no time process
	run=0;
	pno = time_head;
	for(;;)						//schedule all time process in every time arrived;
	{
		if(is_time_run_pro(pno))
		{
			run_pat_entry(pno,0x0L);
			run=1;
		}
		pno=grp_get_pro(pno);
		if(pno == time_head)
			return run;
	}
	return run;
}
/*================================================================*/
int knl_get_rand(int srad);
int knl_get_rand(int srad)
{
	if(srad == 0)
		return 0;
	return(this_us%srad);
}
/*================================================================*/

/* end of time.c */
