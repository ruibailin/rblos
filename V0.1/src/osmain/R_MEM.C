#include "rbltype.h"
#define MAX_USABLE_RAM	0xFFFF

static  WORD RamPtr=0;
static  BFAR  Ram0[MAX_USABLE_RAM];

BFAR *alloc_ram(WORD  len);
BFAR *alloc_ram(WORD  len)
{
	WORD use;
  	BFAR *ptr;
	use=len&0x0001;
	if(use==1) len++;
	use=MAX_USABLE_RAM-RamPtr;
	if(use<len)
		return((VFAR *)0);
	ptr=Ram0+RamPtr;
    for(use=0;use<len;use++)
    Ram0[RamPtr+use]=0;
    
	RamPtr += len;
	return(ptr);

}

/*End of r_mem.c*/
