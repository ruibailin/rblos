
/*------------------------------------
 * r_thread.c
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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int	os_create_thread(void *(*entry) (void *));
int	os_create_thread(void *(*entry) (void *))
{
	int ret;
	pthread_t tid;
	ret = pthread_create(&tid, NULL, entry, NULL);
    if (ret)   exit(ret);
    return ret;
}
/*================================================================*/
#endif
/* end of r_thread.c */
