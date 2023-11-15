
/*------------------------------------
 * process0.c
 * Create:  2023-02-18
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 * Process 0 is monitor and static process
 *
 *
 *
 *------------------------------------
 */

#include "1imp.h"

/*================================================================*/
long    knl_loop_times=0;
extern unsigned int HAL_GetTick(void);
static unsigned int this_ms=0;
static int max_ms_loop=0;
void	sys_proc_00(void *in);
void	sys_proc_00(void *in)
{
	unsigned int last_ms;
	int loop;
	knl_loop_times++;
	if(this_ms==0)
	{
		this_ms=HAL_GetTick();
		last_ms=this_ms;
	}
	else
	{
		last_ms=this_ms;
		this_ms=HAL_GetTick();
	}
	loop=(this_ms-last_ms);
	if(loop>max_ms_loop)
		max_ms_loop=loop;

	usr_print();
}
/*------------------------------------*/
#include <stdio.h>
#define MAX_RUN_MS	1000
extern int  knl_this_pno;
void sys_monitor_00(void);
void sys_monitor_00()
{
	unsigned int next_ms;
	int loop;
	if(this_ms==0)
		return;		//OS not schedule,don't detect
	next_ms=HAL_GetTick();
	loop=(next_ms-this_ms);
	if(loop>MAX_RUN_MS)
		knl_print("EOS,overrun process %d\r\n",knl_this_pno);
}

/*------------------------------------*/
extern unsigned int uwTick;
/**
  * @brief This function is called to increment a global variable "uwTick"
  *        used as application time base.
  * @note In the default implementation, this variable is incremented each 1ms
  *       in SysTick ISR.
 * @note This function is declared as __weak to be overwritten in case of other
  *      implementations in user file.
  * @retval None
  */
void HAL_IncTick(void);
void HAL_IncTick(void)
{
  uwTick += 1;
  sys_monitor_00();
}

/**
  * @brief Provide a tick value in millisecond.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @retval tick value
  */
unsigned int HAL_GetTick(void);
unsigned int HAL_GetTick(void)
{
  return uwTick;
}
/*================================================================*/

/* end of process0.c */
