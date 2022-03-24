/*Borland C3.1*/
#include <dos.h>
#include <conio.h>
#include "rbltype.h"
#include "rblmain.h"
#include "rblstart.h"

/*______________________________________*/

void IniAll(void);
void MainLoop(void);

/*______________________________________*/
int main()
{
  IniAll();
  _enable();
  MainLoop();
  return 0;
}

/*------------------------------------*/
long  SysRunTime=0;
long  CurRunTime=0;

typedef  struct{
  WORD  ms10;       /*Count Of 10 ms */
  WORD  ms100;
  WORD  second;
  WORD  minute;
  WORD  hour;
}COUNT;
static  COUNT SysTimeDate;
static  COUNT CurTimeDate;
/*------------------------------------*/
static  void  deal_sys_date(void);
static  void  deal_sys_date()
{
  SysTimeDate.ms10++;
  if(SysTimeDate.ms10!=10)  return;
  SysTimeDate.ms10=0;
  SysTimeDate.ms100++;
  if(SysTimeDate.ms100!=10)  return;
  SysTimeDate.ms100=0;
  SysTimeDate.second++;
  SysRunTime=CurRunTime;      /*Calculate CPU Busy Rate*/
  CurRunTime=0;
  if(SysTimeDate.second!=60)  return;
  SysTimeDate.second=0;
  SysTimeDate.minute++;
  if(SysTimeDate.minute!=60)  return;
  SysTimeDate.minute=0;
  SysTimeDate.hour++;
}

/*------------------------------------*/
void interrupt far oldThandler(void);
void interrupt far oldThandler()
{
  cli_int();
  outp((unsigned short)0x20,(unsigned char)0x20);
  outp((unsigned short)0xa0,(unsigned char)0x20);
  sti_int();
}
/*------------------------------------*/
void interrupt far newThandler(void);
void interrupt far newThandler()
{
  cli_int();
  deal_sys_date();
  handle_10ms();
  outp((unsigned short)0x20,(unsigned char)0x20);
  outp((unsigned short)0xa0,(unsigned char)0x20);
  sti_int();
}
/*------------------------------------*/
static  void SetVector(void far *);
static  void SetVector(void far *in)
{
  DFAR *ptr;
  WORD num;
  num=0x1c;
  (long)ptr = num*4;
  *ptr=(long)in;
}
/*-----------------------------------*/
/*TIMER CONTROL REGISTERS -- SLOT 0 ADDRESSES*/
#define     DOS_TMR0      (WORD)(0x0040)
#define     DOS_TMR1      (WORD)(0x0041)
#define     DOS_TMR2      (WORD)(0x0042)
#define     DOS_TMRCON    (WORD)(0x0043)

  void  Ini386(void);
  void  Ini386(void)
  {
   outp(DOS_TMRCON, 0x36);/* ;Set timer parameters.     */
   outp(DOS_TMR0, 0x9c);  /* ;Set the timer count (LO byte).*/
   outp(DOS_TMR0, 0x2e);  /* ;Set the timer count (HI byte). */
   /*0x2e9c/1193180hz=10ms*/
  }

/*===========================================================================*/
void  IniAll()
{
  init_all();

  Ini386();
  SetVector((void far *)newThandler); 
}


/*------------------------------------*/
static TempInt=0;

void  MainLoop()
{
  for(;;)
  {
    CurRunTime++;
    if(CurTimeDate.ms10 != SysTimeDate.ms10)
    {
      CurTimeDate.ms10 = SysTimeDate.ms10;
      sch_proc();                 /*10ms Timer  Proc*/
    }
    if(CurTimeDate.ms100 != SysTimeDate.ms100)
    {
      CurTimeDate.ms100 = SysTimeDate.ms100;
     }
    if(CurTimeDate.second != SysTimeDate.second)
    {
      CurTimeDate.second = SysTimeDate.second;
    }
    sch_msg();
  }
}

/*===========================================================================*/

void sti_int();
void cli_int();
void next_ret(WORD state);
void send_ret();

static WORD mask0=0;
void sti_int()
{
  if(mask0==0) return;
  mask0--;
  if(mask0!=0) return;
  _enable();

}

void cli_int()
{
 _disable();
  mask0++;
}

void 	next_ret(WORD state)
{
/*  set_sp(state);*/
}

void	send_ret()
{
}


/*End Of main.c*/

