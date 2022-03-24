#include <stdlib.h>
#include "zxj10.h"
#include "r_pat.h"
/*------------------------------------*/
void  far  NULLPro(BYTE far *in);
void  far NULLPro(BYTE  far *in)
{
}
/*------------------------------------*/
extern  PAT PATPool[64];
WORD  far get_pat_tno(WORD  pno);
WORD  far get_pat_tno(WORD  pno)
{
  WORD  tno;
  tno=(WORD)PATPool[pno].task;
  return(tno);
}
void  far set_pat_tno(WORD  pno,BYTE tno);
void  far set_pat_tno(WORD  pno,BYTE tno)
{
  PATPool[pno].task=tno;
}
void  far set_pat_entry(WORD  pno,void far *entry);
void  far set_pat_entry(WORD  pno,void far *entry)
{
  if(entry == NULL)
  PATPool[pno].entry=&NULLPro;
  else
  (long)(PATPool[pno].entry)=(long)entry;
}
/*End Of r_pat.c*/
