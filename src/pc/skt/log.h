/*
 * log.h
 *
 *  Created on: Nov 16, 2023
 *      Author: stever
 */

#ifndef SRC_PC_SKT_LOG_H_
#define SRC_PC_SKT_LOG_H_
/*================================================================*/
extern void skt_log_packet(char *data, int size);
/*------------------------------------*/
extern void skt_log_hex(char data);
extern void skt_log_ascii(char data);
/*================================================================*/
#endif /* SRC_PC_SKT_LOG_H_ */
