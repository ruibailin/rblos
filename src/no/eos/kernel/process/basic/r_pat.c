
/*------------------------------------
 * r_pat.c
 * Create:  2021-10-16
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 * Process Attribute Table
 *
 *
 *
 *------------------------------------
 */

#include "pat.h"
/*================================================================*/
#define	 PAT_NODE_NUM	MAX_PAT_NUM
#if(PAT_NODE_NUM > MAX_UINTXX-1)
#error
#endif

/*------------------------------------*/
//Get process type number
int get_pat_tno(int pno);
int get_pat_tno(int pno)
{
	int type;
	type =((int)PATPool[pno].type)&MAX_UINTXX;
  return(type);
}
/*------------------------------------*/
void set_pat_tno(int pno,int tno);
void set_pat_tno(int pno,int tno)
{
	PATPool[pno].type =(uintxx)tno;
}
/*------------------------------------*/
//Get process type number
int get_pat_attr(int pno);
int get_pat_attr(int pno)
{
	int attr;
	attr =((int)PATPool[pno].attr)&MAX_UINTXX;
  return(attr);
}
/*------------------------------------*/
void set_pat_attr(int pno,int tno);
void set_pat_attr(int pno,int tno)
{
	PATPool[pno].attr =(uintxx)tno;
}
/*------------------------------------*/
char *get_pat_name(int  pno);
char *get_pat_name(int  pno)
{
	char *name;
	name=PATPool[pno].name;
	return(name);
}

/*------------------------------------*/
void set_pat_name(int  pno,char *name);
void set_pat_name(int  pno,char *name)
{
  PATPool[pno].name=name;
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
int  knl_this_pno=0;
int  knl_last_pno=0;
void run_pat_entry(int  pno,void *in);
void run_pat_entry(int  pno,void *in)
{
	knl_this_pno=pno;
 	PATPool[pno].entry(in);
 	if(PATPool[pno].type == TIME)
 	{
 	 	knl_this_pno=0;
 	 	return;
 	}
 	if(PATPool[pno].type == REAL)
 	{
 	 	knl_this_pno=0;
 	 	return;
 	}
 	knl_last_pno=knl_this_pno;
 	knl_this_pno=0;
}

/*------------------------------------*/
int get_pat_this(void);
int get_pat_this(void)
{
	return knl_this_pno;
}
/*------------------------------------*/
int get_pat_last(void);
int get_pat_last(void)
{
	return knl_last_pno;
}
/*================================================================*/
/* end of r_pat.c */
