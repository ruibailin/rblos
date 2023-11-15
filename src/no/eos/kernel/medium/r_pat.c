
/*------------------------------------
 * r_pat.c
 * Create:  2021-10-16
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
#if EOS_MEDIUM_MODE
/*================================================================*/
#define	 PAT_NODE_NUM	MAX_PAT_NUM
#if(PAT_NODE_NUM > 32767)
#error
#endif

typedef struct{
  void (*entry)(void *);
}PAT;

/*================================================================*/
/*------------------------------------*/
static	PAT PATPool[PAT_NODE_NUM];

/*================================================================*/
/*------------------------------------*/
static void null_p(void *in)
{

}

void	ini_pat_table(void);
void	ini_pat_table()
{
	int i;
	for(i=0;i<PAT_NODE_NUM;i++)
		PATPool[i].entry=null_p;
}
/*------------------------------------*/
int get_pat_tno(int pno);
int get_pat_tno(int pno)
{
  return(0);
}
/*------------------------------------*/
void set_pat_tno(int pno,int tno);
void set_pat_tno(int pno,int tno)
{
}
/*------------------------------------*/
void set_pat_entry(int  pno,void (*entry)(void *));
void set_pat_entry(int  pno,void (*entry)(void *))
{
  PATPool[pno].entry=entry;
}
/*------------------------------------*/
void *get_pat_entry(int  pno);
void *get_pat_entry(int  pno)
{
	void ( *process)(void *in);
	process=PATPool[pno].entry;
	return(process);
}

/*------------------------------------*/
void run_pat_entry(int  pno,void *in);
void run_pat_entry(int  pno,void *in)
{
  PATPool[pno].entry(in);
}
/*================================================================*/
#endif
/* end of r_pat.c */
