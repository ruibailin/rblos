/*
 * log.h
 *
 *  Created on: Nov 16, 2023
 *      Author: stever
 */

#ifndef SRC_PC_rbl_log_H_
#define SRC_PC_rbl_log_H_
/*================================================================*/
extern void rbl_log_packet(char *data, int size);
/*------------------------------------*/
extern void rbl_log_hex(char data);
extern void rbl_log_ascii(char data);
/*================================================================*/
#endif /* SRC_PC_rbl_log_H_ */
