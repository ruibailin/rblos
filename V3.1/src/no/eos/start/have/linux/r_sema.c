
/*------------------------------------
 * r_sema.c
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
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

static sem_t sem_id;
/*------------------------------------*/
void  os_wait_sema(void);
void  os_wait_sema()
{
	sem_wait(&sem_id);
}
/*------------------------------------*/
void  os_post_sema(void);
void  os_post_sema()
{
	sem_post(&sem_id);
 }
/*------------------------------------*/
void os_init_sema(void);
void os_init_sema()
{
 sem_init(&sem_id, 0, 1);
 }

/*================================================================*/
#endif
/* end of r_sema.c */
