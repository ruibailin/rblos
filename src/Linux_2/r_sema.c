
/*semaphore*/

#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

static sem_t sem_id;
/*------------------------------------*/
void  wait_sema(void);
void  wait_sema()
{
	sem_wait(&sem_id);
}
/*------------------------------------*/
void  post_sema(void);
void  post_sema()
{
	sem_post(&sem_id);
 }
/*------------------------------------*/
void init_sema(void);
void init_sema()
{
 sem_init(&sem_id, 0, 1);
 }

/*The End of r_sema.c */
