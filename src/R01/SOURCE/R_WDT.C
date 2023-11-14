#include  "zxj10.h"
#include  "zxfunc.h"
#ifndef   __BORLANDC__    /******************/

#include  "zxhard.h"
static  WORD  clr_flag=0;
void  far clear_watch_dog(void);
void  far clear_watch_dog()
{
  BYTE  led;
  led   =  inp(P3LTC);
  if(clr_flag==0)       /*Bit 1:Clr Watch Dog,This Bit Can't be read*/
  {                     /*7:Green Led,2: Watch Dog;*/
    clr_flag=1;
    led  &=  0x7d;
  }
  else
  {
    clr_flag=0;
    led  |=  0x82;
  }
  outp(P3LTC,led);
}

extern WORD mp_com_state;
void  far WatchDog(BYTE far *ptr);
void  far WatchDog(BYTE far *ptr)
{
  clear_watch_dog();
  SET_TIMER(mp_com_state,(BYTE)0);
  NEXT_STATE(0);
}

#else                     /******************/
#include <dos.h>
#include <mem.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <sys\types.h>

static  unsigned int second=0;
static  unsigned int minute=0;
static  unsigned int hour=0;
void  far WatchDog(BYTE far *ptr);
void  far WatchDog(BYTE far *ptr)
{
  WORD xx,yy;
  long rr;
  struct dostime_t t;
  xx=STATE();
  SET_TIMER((WORD)100,(BYTE)0);
  if(xx==0)
  {
    _dos_gettime(&t);
    hour=t.hour;
    minute=t.minute;
    second=t.second;
    NEXT_STATE(1);
  }
  second++;
  if(second == 60)
  { second=0;minute++;}
  if(minute == 60)
  { minute=0; hour++;}
  if(hour == 24)
  hour=0;

  xx=wherex();
  yy=wherey();
  gotoxy(40,2);
  textcolor(RED);
  rr=get_cpu_rate();
  cprintf("%2d:%02d:%02d  %lx",hour,minute,second,rr);
  gotoxy(xx,yy);
  textcolor(WHITE);
}

void  far clear_watch_dog(void);
void  far clear_watch_dog()
{
}
#endif                    /******************/
