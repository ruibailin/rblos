#include "rbltype.h"
#include "r_pat.h"
#include "r_pcb.h"

extern VFAR UserPro(BFAR *in);
extern VFAR TestPro(BFAR *in);
extern VFAR Test1Pro(BFAR *in);
extern VFAR Test2Pro(BFAR *in);
extern VFAR ScanT(BFAR *in);
/*------------------------------------*/
VFAR NULLPro(BFAR *in);
VFAR NULLPro(BFAR *in)
{
}
/*------------------------------------*/
PAT PATPool[MAX_PCB_NUM]={
/*  task   stack  entry  */
/*000*/  {0,0,&NULLPro},
/*001*/  {0,0,&UserPro},
/*002*/  {0,0,&TestPro},
/*003*/  {0,0,&Test1Pro},
/*004*/  {0,0,&Test2Pro},
/*005*/  {0,0,&ScanT},
/*006*/  {0,0,&NULLPro},
/*007*/  {0,0,&NULLPro},
/*008*/  {0,0,&NULLPro},
/*009*/  {0,0,&NULLPro},

/*010*/  {1,0,&NULLPro},
/*011*/  {2,0,&NULLPro},
/*012*/  {3,0,&NULLPro},
/*013*/  {4,0,&NULLPro},
/*014*/  {0,0,&NULLPro},
/*015*/  {0,0,&NULLPro},
/*016*/  {0,0,&NULLPro},
/*017*/  {0,0,&NULLPro},
/*018*/  {0,0,&NULLPro},
/*019*/  {0,0,&NULLPro},

/*020*/  {0,0,&NULLPro},
/*021*/  {0,0,&NULLPro},
/*022*/  {0,0,&NULLPro},
/*023*/  {0,0,&NULLPro},
/*024*/  {0,0,&NULLPro},
/*025*/  {0,0,&NULLPro},
/*026*/  {0,0,&NULLPro},
/*027*/  {0,0,&NULLPro},
/*028*/  {0,0,&NULLPro},
/*029*/  {0,0,&NULLPro},

/*030*/  {0,0,&NULLPro},
/*031*/  {0,0,&NULLPro}
};
/*End Of r_pat.c*/

/*------------------------------------*/
WFAR get_pat_tno(WORD  pno);
WFAR get_pat_tno(WORD  pno)
{
  WORD  tno;
  tno=(WORD)PATPool[pno].task;
  return(tno);
}
VFAR set_pat_tno(WORD  pno,WORD tno);
VFAR set_pat_tno(WORD  pno,WORD tno)
{
  PATPool[pno].task=tno;
}
VFAR set_pat_entry(WORD  pno,VFAR *entry);
VFAR set_pat_entry(WORD  pno,VFAR *entry)
{
  if(entry == (VFAR *)0)
  PATPool[pno].entry=&NULLPro;
  else
  PATPool[pno].entry=entry;
}

WFAR get_sp(void);
VFAR EXEPROC(WORD  pno,VFAR *msg);
VFAR EXEPROC(WORD  pno,VFAR *msg)
{
	void (FAR *process)(BFAR *in);
	process=PATPool[pno].entry;
	PATPool[pno].stack=get_sp();
	process(msg);
}

/*End Of r_pat.c*/
