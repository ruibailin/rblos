
/*------------------------------------
 * eos_main.c
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


/*================================================================*/
extern void knl_ini_all(void);
extern void knl_run_all(void);
void	eos_main(void);
void	eos_main()
{
	knl_ini_all();
	for(;;)
	{
		knl_run_all();
	}
}

/*================================================================*/

/* end of eos_main.c */
