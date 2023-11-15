
/*------------------------------------
 * pat.h
 * Create:  2023-02-17
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 * Define Process Attribute Table
 *
 *
 *
 *------------------------------------
 */

#ifndef SRC_KERNEL_PROC_PAT_H_
#define SRC_KERNEL_PROC_PAT_H_

#include "1imp.h"
#define	 PAT_NODE_NUM	MAX_PAT_NUM
/*================================================================*/
typedef struct{
	char *name;
    void (*entry)(void *);
    uintxx type;
    uintxx attr;
}PAT;

extern PAT PATPool[PAT_NODE_NUM];
extern int  knl_this_pno;

//define type of process
#define	DUM_PROC		0x00		//dummy process, no scheduled,just saved resource
#define IDLE_PROC		0x01		//process is scheduled when CPU is idle(no SLOT, MSG and TIME to run)
#define SLOT_PROC		0x02		//process is scheduled by time slot and no TIME and MSG proc to run in this loop
#define MSG_PROC		0x03		//process is scheduled by message and no TIME proc to run in this loop
#define TIME_PROC		0x04		//process is scheduled every a fixed time, the time length is defined by attr.
#define REAL_PROC		0x05		//Real time process,will be scheduled every main loop
#define MAX_TYPE_NUM	6
/*================================================================*/

#endif 
/* end of pat.h */
