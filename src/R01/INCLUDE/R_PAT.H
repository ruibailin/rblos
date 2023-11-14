#ifndef _r_pat_h
#define _r_pat_h
/*------------------------------------*/
typedef struct{
  BYTE  task;         /*0:Real Proc,1:10ms,2:100ms,3:1000ms*/
  BYTE  neme[9];
  WORD  stack;
  void  (far *entry)(BYTE far *);
}PAT;
/*------------------------------------*/
extern  WORD  far get_pat_tno(WORD  pno);
extern  void  far set_pat_tno(WORD  pno,BYTE tno);
extern  void  far set_pat_entry(WORD  pno,void far *entry);

extern  void  far EXEPROC(BYTE far *in);  /*Module:r_rpc.asm*/
extern  void  far NEXTRET(void);
/*------------------------------------*/
#endif
/*End of r_pat.h*/

