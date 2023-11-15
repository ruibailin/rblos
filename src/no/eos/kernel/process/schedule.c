
/*------------------------------------
 * proc.c
 * Create:  2023-02-18
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */

#include "./group/2exp.h"

/*================================================================*/
void knl_ini_pro(void);
void knl_ini_pro()
{
	grp_ini_pro();

	grp_ini_dum_pro();
	grp_ini_idle_pro();
	grp_ini_msg_pro();
	grp_ini_slot_pro();
	grp_ini_time_pro();
	grp_ini_real_pro();

	grp_run_msg_pro();
}

void knl_run_real_p(void);
void knl_run_real_p()
{
	grp_run_real_pro();
}

int knl_run_time_p(void);
int knl_run_time_p()
{
	int res;
	res=grp_run_time_pro();
	return res;
}

void knl_run_idle_p(void);
void knl_run_idle_p()
{
	grp_run_idle_pro();
}

/*================================================================*/

/* end of proc.c */
