#ifndef _r_tcb_h
#define _r_tcb_h
/*------------------------------------*/
extern	void	ini_tcb_list(void);
extern	int		get_node_tcb(int tno,int pno);
extern	void	set_node_tcb(int node,int len);
extern	void	reset_node_tcb(int node);
extern	void	run_tcb_list(void);
extern	int		get_tcb_arrived(void);
extern	void	free_tcb_arrived(int node);
extern	int		get_tcb_tno(int node);
extern	int		get_tcb_pno(int node);

/*------------------------------------*/
#endif

/*End Of tcb.h*/

