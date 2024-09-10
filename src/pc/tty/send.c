/*
 * send.c
 *
 *  Created on: May 16, 2024
 *      Author: stever
 */


#include "1imp.h"
/*================================================================*/
// Writes bytes to the serial port, returning 0 on success and -1 on failure.
#include <unistd.h>
int rbl_tty_write_port(int fd,char * buffer, int size);
int rbl_tty_write_port(int fd,char * buffer, int size)
{
  ssize_t result;
  result = write(fd, buffer, size);
  if (result != (ssize_t)size)
  {
    perror("failed to write to port");
    return -1;
  }
  return 0;
}
/*------------------------------------*/
int rbl_tty_send_usb_uart(int usb_fd,char *c,int size);
int rbl_tty_send_usb_uart(int usb_fd,char *c,int size)
{
	if(usb_fd<0)
		return -1;
	int ret;
//	ret = send(usb_fd,c,size,MSG_DONTWAIT);
	ret = rbl_tty_write_port(usb_fd,c,size);
	return ret;
}

/*================================================================*/
/* end of send.c */
