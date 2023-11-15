
/*------------------------------------
 * schedule.c
 * Create:  2023-02-21
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */

#include "r_msg.h"

/*================================================================*/
int knl_this_msg=0;
void	knl_ini_msg(void);
void	knl_ini_msg()
{
	ini_msg_list();
}

extern	void	run_pat_entry(int  pno,void *in);
int	knl_run_msg(void);
int	knl_run_msg()
{
	int msg;
	int pno;
	void *in;

	msg=get_msg_arrived();
	if(msg==EventIdleQHead)
		return 0;
	if(msg==EventBusyQHead)
		return 0;

	knl_this_msg=msg;
	pno=get_msg_dest(msg);
	in=get_msg_body(msg);
	run_pat_entry(pno,in);
	free_msg_arrived(msg);
	knl_this_msg=0;
	return 1;
}

/*================================================================*/

/* end of msg_schedule.c */
