/*
 * r_pat.c
 *
 *  Created on: Apr 13, 2021
 *      Author: steve
 */


#include "0ctr.h"
/*================================================================*/
#include "r_pat.h"

#define	 MAX_NODE_NUM	MAX_PAT_NUM
typedef struct{
  int  task;			/*0:Real Proc,1:10ms,2:100ms,3:1000ms*/
  void (*entry)(void *);
}PAT;

static  void  null_proc(void *in);
static  void  null_proc(void *in)
{
}

/*================================================================*/
/*------------------------------------*/
static	PAT PATPool[MAX_NODE_NUM]={
/*  task   entry  */
/*000*/  {0,&null_proc},
/*001*/  {0,&null_proc},
/*002*/  {0,&null_proc},
/*003*/  {0,&null_proc},

/*004*/  {0,&null_proc},
/*005*/  {0,&null_proc},
/*006*/  {0,&null_proc},
/*007*/  {0,&null_proc},
/*008*/  {0,&null_proc},
/*009*/  {0,&null_proc},

/*010*/  {0,&null_proc},
/*011*/  {0,&null_proc},
/*012*/  {0,&null_proc},
/*013*/  {0,&null_proc},
/*014*/  {0,&null_proc},
/*015*/  {0,&null_proc},
/*016*/  {0,&null_proc},
/*017*/  {0,&null_proc},
/*018*/  {0,&null_proc},
/*019*/  {0,&null_proc},

/*020*/  {0,&null_proc},
/*021*/  {0,&null_proc},
/*022*/  {0,&null_proc},
/*023*/  {0,&null_proc},
/*024*/  {0,&null_proc},
/*025*/  {0,&null_proc},
/*026*/  {0,&null_proc},
/*027*/  {0,&null_proc},
/*028*/  {0,&null_proc},
/*029*/  {0,&null_proc},

/*030*/  {0,&null_proc},
/*031*/  {0,&null_proc},
/*032*/  {0,&null_proc},
/*033*/  {0,&null_proc},
/*034*/  {0,&null_proc},
/*035*/  {0,&null_proc},

};

/*================================================================*/
/*------------------------------------*/
int get_pat_tno(int pno);
int get_pat_tno(int pno)
{
  int  tno;
  tno=PATPool[pno].task;
  return(tno);
}
/*------------------------------------*/
void set_pat_tno(int pno,int tno);
void set_pat_tno(int pno,int tno)
{
  PATPool[pno].task=tno;
}
/*------------------------------------*/
void set_pat_entry(int  pno,void *entry);
void set_pat_entry(int  pno,void *entry)
{
  if(entry == (void *)0L)
  PATPool[pno].entry=&null_proc;
  else
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

/*================================================================*/
/* end of r_pat.c */
