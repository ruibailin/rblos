#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "zxj10.h"
#include "zxtype.h"
#include "zxfunc.h"
#include "zxevent.h"
#include  "r_tcb.h"

extern TCB far *TCBPool;
/*------------------------------------*/
/*Browse a TAG In Queue */
static  void  BrowseTAG(WORD item);
void  BrowseTAG(WORD item)
{
  WORD next;
  next=TCBPool[item].tag.next;
  for(;;)
  {
    if(next == item) break;
    next=TCBPool[next].tag.next;
  }
}
WORD  isdn[302];
void  aaaa(WORD ii);
void  aaaa(WORD ii)
{
ii=ii;
}
WORD  pppp=0;
WORD  tttt;
void  far TestPro(BYTE far *ptr);
void  far TestPro(BYTE far *ptr)
{
  WORD  ss,ii,jj;
  CSN   csn;
  ss=STATE();
  if(ss==0)
  {
    for(ii=0;ii<300;ii++)
    isdn[ii]=0xffff;
    csn.isdn=99;
    EXTRA_SET_TIMER(40,TIMER1,csn);
    NEXT_STATE(1);
  }

  jj=((CSN far *)ptr)->isdn;
 // printf(" %d",jj);
  for(ii=0;ii<300;ii++)
  {
    EXTRA_KILL_TIMER(isdn[ii]);
    jj=random(200)+2;
    jj *= 5;
    csn.isdn=ii;
    isdn[ii]=EXTRA_SET_TIMER(jj,TIMER1,csn);
  }
}

WORD  lll[4];
void  far Test1Pro(BYTE far *ptr);
void  far Test1Pro(BYTE far *ptr)
{
  WORD  ss,ii,jj;
  ss=STATE();
  if(ss==0)
  {
    lll[0]=0;
    SET_TIMER(9,TIMER1);
    lll[1]=0;
    SET_TIMER(99,TIMER2);
    lll[2]=0;
    SET_TIMER(999,TIMER3);
    SET_TIMER(9999,TIMER4);
    NEXT_STATE(1);
  }
  ss=EVENT();
  switch(ss)
  {
    case  Timer1Event:
	  printf(" 1=%d ",lll[0]);
	  break;
    case  Timer2Event:
	  printf(" 2=%d ",lll[1]);
	  break;
    case  Timer3Event:
	  printf(" 3=%d ",lll[2]);
	 lll[0]=0;
	 lll[1]=0;
	 lll[2]=0;
	  SET_TIMER(9,TIMER1);
	  SET_TIMER(99,TIMER2);
	  SET_TIMER(999,TIMER3);
	  break;
    default:
	  break;
  }
}

WORD  setlen[32];
WORD  icclen[32];
WORD  mytid[32];
void  far Test2Pro(BYTE far *ptr);
void  far Test2Pro(BYTE far *ptr)
{
  WORD  ss,ii,jj;
  CSN   csn;
  ss=STATE();
  if(ss==0)
  {
    for(ii=0;ii<30;ii++)
    {
      icclen[ii]=0;
      setlen[ii]=random(900)+1;
      csn.isdn=ii;
      mytid[ii]=EXTRA_SET_TIMER(setlen[ii],TIMER1,csn);
    }
    NEXT_STATE(1);
  }

  ii=((CSN far *)ptr)->isdn;
  if(setlen[ii]>icclen[ii])
  jj=setlen[ii]-icclen[ii];
  else
  jj=icclen[ii]-setlen[ii];

  if(jj>6)
  printf(" \n SET %d,ERR %d",setlen[ii],jj);

  icclen[ii]=0;
  setlen[ii]=random(900)+1;
  csn.isdn=ii;
  mytid[ii]=EXTRA_SET_TIMER(setlen[ii],TIMER1,csn);
}
void  far ScanT(BYTE far *ptr);
void  far ScanT(BYTE far *ptr)
{
  WORD ii;
  lll[0]++;
  lll[1]++;
  lll[2]++;
  for(ii=0;ii<30;ii++)
  {
   icclen[ii] ++;
   if(icclen[ii]>(setlen[ii]+1))
   BrowseTAG(mytid[ii]);
  }
}

WORD far SendToMP(WORD event,BYTE far * Data,WORD len,WORD d_pno,WORD s_pno);
WORD far SendToMP(WORD event,BYTE far * Data,WORD len,WORD d_pno,WORD s_pno)
{
}

