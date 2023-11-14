#ifndef  __BORLANDC__
/****************** __MICROSOFT__ ****************/
#include "zxj10.h"
typedef struct{
  WORD  LoWord;
  WORD  HiWord;
}DWORD;
typedef union{
  BYTE  far *pointer;
  DWORD      address;
}U_PTR;
static  WORD  RamSeg=0x0000;      /*ram start useable address*/
static  WORD  RomSeg=0xd000;      /*flash memory start useable address*/

extern  WORD  far GetSSSP(void);
BYTE  far *alloc_ram(WORD  len);
BYTE  far *alloc_ram(WORD  len)
{
  U_PTR   ptr;
  long    ll;
  if(RamSeg == 0x0000)
  RamSeg=GetSSSP();              /*Get Max Useable Segment*/

  ptr.address.HiWord=RamSeg;
  ptr.address.LoWord=0x0000;

  ll=(unsigned long)len+15;
  len=(WORD)(ll>>4);
  len += RamSeg;
  if(len < 0x4000)
  {
    RamSeg=len;
    return(ptr.pointer);
  }
  ptr.address.HiWord=0x0000;
  ptr.address.LoWord=0x0000;
  return(ptr.pointer);
}
BYTE  far *alloc_rom(WORD  len);
BYTE  far *alloc_rom(WORD  len)
{
  U_PTR   ptr;
  ptr.address.HiWord=0x0000;
  ptr.address.LoWord=0x0000;
  return(ptr.pointer);
}
#else
/****************** __BORLANDC__ ****************/
#include <stdlib.h>
#include "zxj10.h"
static  WORD  RamOff[4]={0,0,0,0};
static  WORD  RomOff=0;
static  BYTE  far *RamPtr[2];
static  BYTE  far *RomPtr;

static  BYTE  far Ram0[0xffff];
static  BYTE  far Ram1[0xffff];
//static  BYTE  far Ram2[65535];
//static  BYTE  far Ram3[65535];
static  BYTE  far Rom0[0xffff];

BYTE  far *alloc_ram(WORD  len);
BYTE  far *alloc_ram(WORD  len)
{
  WORD  ii;
  WORD  use;
  BYTE  far *ptr;
  if(RamOff[0]==0)
  {
	 RamPtr[0]=Ram0;
	 RamPtr[1]=Ram1;
//    RamPtr[2]=Ram2;
//    RamPtr[3]=Ram3;
  }
//  for(ii=0;ii<4;ii++)
  for(ii=0;ii<2;ii++)
  {
	 ptr=RamPtr[ii]+RamOff[ii];
	 use=0xffff-RamOff[ii];
	 if(use<len)
	 continue;
	 RamOff[ii] += len;
	 return(ptr);
  }
  return(NULL);
}

BYTE  far *alloc_rom(WORD  len);
BYTE  far *alloc_rom(WORD  len)
{
  WORD  use;
  BYTE  far *ptr;
//
  if(RomOff==0)
  RomPtr=Rom0;
  ptr=RomPtr+RomOff;
  use=0xffff-RomOff;

  if(use<len)
  return(NULL);
  RomOff += len;
  return(ptr);
}
#endif

/*End of r_mem.c*/
