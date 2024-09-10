/*
 * 1imp.h
 *
 *  Created on: May 8, 2024
 *      Author: stever
 */

#ifndef rbl_tty_1IMP_H_
#define rbl_tty_1IMP_H_
#include <termios.h>
/*================================================================*/
#include <stdio.h>
#include <fcntl.h>
#include <sys/socket.h>
/*------------------------------------*/
extern int rbl_tty_usb_fd;
#define rbl_print(x...)  	printf(x);
/*================================================================*/
#endif /* rbl_tty_1IMP_H_ */
