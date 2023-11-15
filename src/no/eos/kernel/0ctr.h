
/*------------------------------------
 * 0ctr.h
 * Create:  2021-10-16
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 * Embedded OS Kernel Configuration
 *
 *
 *
 *------------------------------------
 */



#ifndef EOS_KERNEL_0CTR_H_
#define EOS_KERNEL_0CTR_H_


/*================================================================*/
#define EOS_TINY_MODE	0		//8 bit system or tiny ram
#define	EOS_SMALL_MODE	0		//16 bit system or small ram
#define EOS_MEDIUM_MODE	1		//32 bit system
#define EOS_HUGE_MODE	0		//64 bit system

#define	EOS_DEBUG		0

#if EOS_TINY_MODE
typedef unsigned char  	uintxx;//in order to save memory
#define	MAX_UINTXX     	0xFF
#define	MAX_MSG_NUM		200
#define	MAX_PAT_NUM		32
#define	MAX_TCB_NUM		200
#endif

#if EOS_SMALL_MODE
typedef unsigned short  uintxx;
#define	MAX_UINTXX		0xFFFF
#define	MAX_MSG_NUM		240
#define	MAX_PAT_NUM		64
#define	MAX_TCB_NUM		360
#endif

#if EOS_MEDIUM_MODE
typedef unsigned int  	uintxx;
#define	MAX_UINTXX		0xFFFFFFFF
#define	MAX_MSG_NUM		240
#define	MAX_PAT_NUM		64
#define	MAX_TCB_NUM		240
#endif
/*================================================================*/
#endif
/* end of 0ctr.h */
