/*
 * init.c
 *
 *  Created on: May 8, 2024
 *      Author: stever
 */


#include "1imp.h"
/*================================================================*/
// Uses POSIX serial port functions to send and receive data from a Jrk G2.
// NOTE: The Jrk's input mode must be "Serial / I2C / USB".
// NOTE: The Jrk's serial mode must be set to "USB dual port" if you are
//   connecting to it directly via USB.
// NODE: The Jrk's serial mode must be set to "UART" if you are connecting to
//   it via is TX and RX lines.
// NOTE: You might need to change the 'const char * device' line below to
//   specify the correct serial port.

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <termios.h>

// Opens the specified serial port, sets it up for binary communication,
// configures its read timeouts, and sets its baud rate.
// Returns a non-negative file descriptor on success, or -1 on failure.
int rbl_tty_open_serial_port(const char *device,unsigned int baud_rate);
int rbl_tty_open_serial_port(const char *device,unsigned int baud_rate)
{
  int fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1)
  {
    rbl_print("USB Serial %s fail to Open\r\n", device);
    return -1;
  }

  // Flush away any bytes previously read or written.
  int result = tcflush(fd, TCIOFLUSH);
  if (result)
  {
	 rbl_print("tcflush failed\r\n");  // just a warning, not a fatal error
  }

  // Get the current configuration of the serial port.
  struct termios options;
  result = tcgetattr(fd, &options);
  if (result)
  {
	  rbl_print("tcgetattr failed\r\n");
    close(fd);
    return -1;
  }

  // Turn off any options that might interfere with our ability to send and
  // receive raw binary bytes.
  options.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
  options.c_oflag &= ~(ONLCR | OCRNL);
  options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);

  // Set up timeouts: Calls to read() will return as soon as there is
  // at least one byte available or when 100 ms has passed.
  options.c_cc[VTIME] = 1;
  options.c_cc[VMIN] = 0;

  // This code only supports certain standard baud rates. Supporting
  // non-standard baud rates should be possible but takes more work.
  switch (baud_rate)
  {
  case 4800:
	  cfsetospeed(&options, B4800);
	  cfsetispeed(&options, B4800);
	  break;
  case 9600:
	  cfsetospeed(&options, B9600);
	  cfsetispeed(&options, B9600);
	  break;
  case 19200:
	  cfsetospeed(&options, B19200);
	  cfsetispeed(&options, B19200);
	  break;
  case 38400:
	  cfsetospeed(&options, B38400);
	  cfsetispeed(&options, B38400);
	  break;
  case 115200:
	  cfsetospeed(&options, B115200);
	  cfsetispeed(&options, B115200);
	  break;
  default:
    rbl_print("warning: baud rate %u is not supported, using 9600.\n", baud_rate);
    cfsetospeed(&options, B9600);
    cfsetispeed(&options, B9600);
    break;
  }

  result = tcsetattr(fd, TCSANOW, &options);
  if (result)
  {
    rbl_print("tcsetattr failed\r\n");
    close(fd);
    return -1;
  }
  rbl_print("Open USB Serial %s at baud rate %d\r\n",device,baud_rate);
  return fd;
}

/*------------------------------------*/
//static const char usb_device[] = "/dev/ttyS73";

int rbl_tty_init_usb_uart(char *usb_device,unsigned int baud);
int rbl_tty_init_usb_uart(char *usb_device,unsigned int baud)
{
	int usb_fd;
	usb_fd = -1;
	usb_fd = rbl_tty_open_serial_port(usb_device,baud);
//	usb_fd = rbl_tty_open_serial_port(usb_device,115200);
	return usb_fd;
}
/*================================================================*/
/* end of init.c */
