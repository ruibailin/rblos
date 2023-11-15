
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


/*================================================================*/
extern void knl_ini_ir_func(void);
extern void knl_ini_msg(void);
extern void knl_ini_tim(void);
extern void	knl_ini_pcb(void);
extern void knl_ini_pro(void);

void knl_ini_all(void);
void knl_ini_all()
{
	knl_ini_ir_func();
	knl_ini_msg();
	knl_ini_tim();
	knl_ini_pcb();
	knl_ini_pro();
}

extern unsigned int knl_get_ir_flag(void);
extern void knl_run_ir_func(void);
extern void knl_run_real_p(void);
extern int knl_run_time_p(void);
extern int	knl_run_tim(void);
extern int	knl_run_msg(void);
extern void knl_run_idle_p(void);

void knl_run_all(void);
void knl_run_all()
{
	unsigned int res;
	res=knl_get_ir_flag();
	if(res)
		knl_run_ir_func();

	knl_run_real_p();
	knl_run_time_p();

	res=knl_run_tim();
	if(res)
		return;
	res=knl_run_msg();
	if(res)
		return;
	knl_run_idle_p();
}

/*================================================================*/

/* end of schedule.c */
