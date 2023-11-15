
#include <signal.h>
#include <semaphore.h>
#include <pthread.h>

static pthread_mutex_t	sys_lock;	//»¥³âËø

/*------------------------------------*/
void ini_lock(void);
void ini_lock()
{
	pthread_mutex_init (&sys_lock, (pthread_mutexattr_t *)NULL);
}
/*------------------------------------*/
void unini_lock(void);
void unini_lock()
{
	pthread_mutex_destroy(&sys_lock);
}
/*------------------------------------*/
void lock_lock(void);
void lock_lock()
{	
	pthread_mutex_lock (&sys_lock);
}
/*------------------------------------*/
void unlock_lock(void);
void unlock_lock()
{
	pthread_mutex_unlock(&sys_lock);
}
/*End of r_lock.c*/