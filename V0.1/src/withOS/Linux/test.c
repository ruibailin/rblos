#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "rbltype.h"
#include "rbltype.h"
#include "rblfunc.h"



/*------------------------------------*/
VFAR TestPro(BFAR *ptr);
VFAR TestPro(BFAR *ptr)
{
  WORD  ss,ii,jj;
    ii=random(10);
    SET(ii+1,0);
    printf(" 1=%d ",ii);  	
    return;
}

WORD  lll[4];
VFAR Test1Pro(BFAR *ptr);
VFAR Test1Pro(BFAR *ptr)
{
  
}


VFAR Test2Pro(BFAR *ptr);
VFAR Test2Pro(BFAR *ptr)
{

}

VFAR  ScanT(BFAR *ptr);
VFAR  ScanT(BFAR *ptr)
{
 
}



VFAR UserPro(BFAR *ptr);
VFAR UserPro(BFAR *ptr)
{
  
 }

