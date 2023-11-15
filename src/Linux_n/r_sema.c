
/*semaphore*/
#include "r_pat.h"
#include <semaphore.h>
#define		PAT_LIST_NUM		4
#define		MAX_PAT_NUM		32
#define	MAX_NODE_NUM	PAT_LIST_NUM+MAX_PAT_NUM
static sem_t sem_id[MAX_NODE_NUM];
/*------------------------------------*/
void  wait_sema(int pno);
void  wait_sema(int pno)
{
	sem_wait(&sem_id[pno]);
}
/*------------------------------------*/
void  post_sema(int pno);
void  post_sema(int pno)
{
	sem_post(&sem_id[pno]);
 }
/*------------------------------------*/
void init_sema(void);
void init_sema()
{
	int ii;
	for(ii=0;ii<MAX_NODE_NUM;ii++)
		sem_init(&sem_id[ii], 0, 0);

}

/*The End of r_sema.c */
