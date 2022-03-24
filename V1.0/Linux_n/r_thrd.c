
/*linux thread*/
#include "r_pat.h"
#define		PAT_LIST_NUM		4
#define		ProcRealQueue   	0
#define		Proc10msQueue	1
#define		Proc100msQueue	2
#define		Proc1sQueue		3
#define		MAX_PAT_NUM		32
/*================================================================*/
#define		MAX_NODE_NUM	MAX_PAT_NUM+PAT_LIST_NUM
static	int	PPidPool[MAX_NODE_NUM];
/*--------------------------------------*/
static	int	find_pno_by_ppid(int pid);
static	int	find_pno_by_ppid(int pid)
{
	int ii;
	for(ii=0;ii<MAX_NODE_NUM;ii++)
		if(PPidPool[ii]==pid) 	break;
	return ii;
}

/*================================================================*/
#include "r_pcb.h"
#include "r_msg.h"
#include "r_sema.h"
#include "r_lock.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

/*--------------------------------------*/
static void *pthread_entry(void *arg);
static void *pthread_entry(void *arg)
{
	pid_t ppid;
	int node;
	int pno,tno;
	int ii;

	pno=*((int *)arg);
	ppid=syscall(SYS_gettid);	//get LWP�̵߳�tid
	PPidPool[pno]=(int)ppid;
	tno=get_pat_tno(pno);
	for(;;)
	{
		switch(tno)
		{
			case ProcRealQueue:
				wait_sema(pno);
				lock_lock();
				node=get_pcb_msg(pno);
				unlock_lock();
				set_pcb_event(pno,node);
				run_pcb_node(pno);
				lock_lock();
				free_msg_arrived(node);
				unlock_lock();
			break;
			case Proc10msQueue:
				usleep(10000);
				run_pcb_node(pno);
			break;
			case Proc100msQueue:
				usleep(100000);
				run_pcb_node(pno);
			break;
			case Proc1sQueue:
				for(ii=0;ii<10;ii++) usleep(100000);
				run_pcb_node(pno);
			break;
		default:
			return((void *)0L);
		}
	}
	return((void *)0L);
}

/*--------------------------------------*/
static	int  ini_sys_pno[MAX_NODE_NUM];
void	ini_linux_thread(void);
void	ini_linux_thread(void)
{
	pthread_t tid;
	int ret,pno;
	
	for(pno=0;pno<MAX_NODE_NUM;pno++)
	{
	        ini_sys_pno[pno]=pno;
		ret = pthread_create(&tid, (void *)0L, pthread_entry, &ini_sys_pno[pno]);
		if (ret)   exit(ret);
	}
}

/*--------------------------------------*/
int	get_sys_pno(void);
int	get_sys_pno(void)
{
	pid_t ppid;
	int pno;

	ppid=syscall(SYS_gettid);
	pno=find_pno_by_ppid((int)ppid);
	if(pno < MAX_NODE_NUM)	return(pno);
	return(-1);

}


/*The End of r_thread.c */
