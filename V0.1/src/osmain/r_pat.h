#ifndef _r_pat_h
#define _r_pat_h
#include "rbltype.h"
/*------------------------------------*/
typedef struct{
  WORD  task;         /*0:Real Proc,1:10ms,2:100ms,3:1000ms*/
  WORD  stack;
  void  (FAR *entry)(BFAR *);
}PAT;
extern  PAT PATPool[32];
/*------------------------------------*/
extern  WFAR get_pat_tno(WORD  pno);
extern  VFAR set_pat_tno(WORD  pno,WORD tno);
extern  VFAR set_pat_entry(WORD  pno,VFAR *entry);

extern  VFAR EXEPROC(WORD  pno,VFAR *in);  /*Module:r_rpc.asm*/
/*------------------------------------*/
#endif
/*End of r_pat.h*/

