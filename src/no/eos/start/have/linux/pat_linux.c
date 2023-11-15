
/*------------------------------------
 * pat.c
 * Create:  2023-02-17
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 * User Process register here
 *
 *
 *
 *------------------------------------
 */


#include "../../../../eos/kernel/process/basic/pat.h"
/*================================================================*/
/*------------------------------------*/
static void null_p(void *in)
{

}
/*------------------------------------*/
extern void	sys_proc_00(void *in);
extern void	sys_timer(void *in);
extern void	sys_idler(void *in);
extern void	sys_comer(void *in);

extern void real_pro10(void *ptr);
extern void real_pro20(void *ptr);
extern void  watch_dog(void *ptr);
/*------------------------------------*/
PAT PATPool[MAX_PAT_NUM]={
/*       name      		entry  		type	attr	*/
/*000*/  {"System 00", 	&sys_proc_00,	REAL,		0},
/*001*/  {"Null Pro", 	&null_p,	0,		0},
/*002*/  {"Null Pro", 	&null_p,	0,		0},
/*003*/  {"Null Pro", 	&null_p,	0,		0},
/*004*/  {"Null Pro", 	&null_p,	0,		0},
/*005*/  {"Null Pro", 	&null_p,	0,		0},
/*006*/  {"Null Pro", 	&null_p,	0,		0},
/*007*/  {"Null Pro", 	&null_p,	0,		0},
/*008*/  {"Null Pro", 	&null_p,	0,		0},
/*009*/  {"Null Pro", 	&watch_dog,	MSG,		0},
/*010*/  {"Null Pro", 	&real_pro10,	MSG,		0},
/*011*/  {"Null Pro", 	&null_p,	0,		0},
/*012*/  {"Null Pro", 	&null_p,	0,		0},
/*013*/  {"Null Pro", 	&null_p,	0,		0},
/*014*/  {"Null Pro", 	&null_p,	0,		0},
/*015*/  {"Null Pro", 	&null_p,	0,		0},
/*016*/  {"Null Pro", 	&null_p,	0,		0},
/*017*/  {"Null Pro", 	&null_p,	0,		0},
/*018*/  {"Null Pro", 	&null_p,	0,		0},
/*019*/  {"Null Pro", 	&null_p,	0,		0},
/*020*/  {"Null Pro", 	&real_pro20,	MSG,		0},
/*021*/  {"Null Pro", 	&null_p,	0,		0},
/*022*/  {"Null Pro", 	&null_p,	0,		0},
/*023*/  {"Null Pro", 	&null_p,	0,		0},
/*024*/  {"Null Pro", 	&null_p,	0,		0},
/*025*/  {"Null Pro", 	&null_p,	0,		0},
/*026*/  {"Null Pro", 	&null_p,	0,		0},
/*027*/  {"Null Pro", 	&null_p,	0,		0},
/*028*/  {"Null Pro", 	&null_p,	0,		0},
/*029*/  {"Null Pro", 	&null_p,	0,		0},
/*030*/  {"Null Pro", 	&null_p,	0,		0},
/*031*/  {"Null Pro", 	&null_p,	0,		0},
/*032*/  {"Null Pro", 	&null_p,	0,		0},
/*033*/  {"Null Pro", 	&null_p,	0,		0},
/*034*/  {"Null Pro", 	&null_p,	0,		0},
/*035*/  {"Null Pro", 	&null_p,	0,		0},
/*036*/  {"Null Pro", 	&null_p,	0,		0},
/*037*/  {"Null Pro", 	&null_p,	0,		0},
/*038*/  {"Null Pro", 	&null_p,	0,		0},
/*039*/  {"Null Pro", 	&null_p,	0,		0},
/*040*/  {"Null Pro", 	&null_p,	0,		0},
/*041*/  {"Null Pro", 	&null_p,	0,		0},
/*042*/  {"Null Pro", 	&null_p,	0,		0},
/*043*/  {"Null Pro", 	&null_p,	0,		0},
/*044*/  {"Null Pro", 	&null_p,	0,		0},
/*045*/  {"Null Pro", 	&null_p,	0,		0},
/*046*/  {"Null Pro", 	&null_p,	0,		0},
/*047*/  {"Null Pro", 	&null_p,	0,		0},
/*048*/  {"Null Pro", 	&null_p,	0,		0},
/*049*/  {"Null Pro", 	&null_p,	0,		0},
/*050*/  {"Null Pro", 	&null_p,	0,		0},
/*051*/  {"Null Pro", 	&null_p,	0,		0},
/*052*/  {"Null Pro", 	&null_p,	0,		0},
/*053*/  {"Null Pro", 	&null_p,	0,		0},
/*054*/  {"Null Pro", 	&null_p,	0,		0},
/*055*/  {"Null Pro", 	&null_p,	0,		0},
/*056*/  {"Null Pro", 	&null_p,	0,		0},
/*057*/  {"Null Pro", 	&null_p,	0,		0},
/*058*/  {"Null Pro", 	&null_p,	0,		0},
/*059*/  {"Null Pro", 	&null_p,	0,		0},
/*060*/  {"Com outside", 	&sys_comer,	MSG,		0},
/*061*/  {"Timer Proc", 	&sys_timer,	TIME,		1},
/*062*/  {"Idler Proc", 	&sys_idler,	IDLE,		0},
/*063*/  {"Null Pro", 	&null_p,	0,		0},
};

/*================================================================*/

/* end of pat.c */
