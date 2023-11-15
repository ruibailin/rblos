/*
 * eos_event.h
 *
 *  Created on: May 19, 2023
 *      Author: stever
 */

#ifndef SRC_EOS_EOS_EVENT_H_
#define SRC_EOS_EOS_EVENT_H_
#include "eos_timer.h"
/*================================================================*/
#define	EOS_NO_EVENT			0
#define	EOS_IS_EVENT			1
/*------------------------------------*/
#define	EOS_TIMER0_EVENT			(EOS_IS_EVENT+EOS_TIMER0)
#define	EOS_TIMER1_EVENT			(EOS_IS_EVENT+EOS_TIMER1)
#define	EOS_TIMER2_EVENT			(EOS_IS_EVENT+EOS_TIMER2)
#define	EOS_TIMER3_EVENT			(EOS_IS_EVENT+EOS_TIMER3)

#define	EOS_USER_EVENT			(EOS_TIMER3_EVENT+1)
/*================================================================*/
#endif /* SRC_EOS_EOS_EVENT_H_ */
