#ifndef _r_pat_h
#define _r_pat_h

#define		PAT_LIST_NUM	4
#define		ProcRealQueue   0
#define		Proc10msQueue	1
#define		Proc100msQueue	2
#define		Proc1sQueue		3
#define		MAX_PAT_NUM		32
/*------------------------------------*/
extern	int		get_pat_tno(int pno);
extern	void	set_pat_tno(int pno,int tno);
extern	void	set_pat_entry(int  pno,void *entry);
extern	void	*get_pat_entry(int  pno);
#endif
/*End of r_pat.h*/

