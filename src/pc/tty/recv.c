/*
 * recv.c
 *
 *  Created on: May 8, 2024
 *      Author: stever
 */


#include "1imp.h"
/*================================================================*/
// Reads bytes from the serial port.
// Returns after all the desired bytes have been read, or if there is a
// timeout or other error.
// Returns the number of bytes successfully read into the buffer, or -1 if
// there was an error reading.
#include <unistd.h>
int rbl_tty_read_port(int fd,char * buffer, int size);
int rbl_tty_read_port(int fd,char * buffer, int size)
{
  size_t received = 0;
  while (received < size)
  {
    ssize_t r = read(fd, buffer + received, size - received);
    if (r < 0)
    {
 //     perror("failed to read from port");
      return -1;
    }
    if (r == 0)
    {
      // Timeout
      break;
    }
    received += r;
  }
  return received;
}
/*------------------------------------*/
int rbl_tty_read_usb_uart(int usb_fd,char *c);
int rbl_tty_read_usb_uart(int usb_fd,char *c)
{
	if(usb_fd<0)
		return -1;
	int ret;
//	ret = read(usb_fd,c,1);
//	ret = recv(usb_fd,c,1,O_NONBLOCK);
	char cc[16];
	ret = rbl_tty_read_port(usb_fd,cc,1);
	if(ret == 1)
		*c=cc[0];
	else
		*c='\0';
	return ret;
}
/*================================================================*/
/* end of recv.c */
