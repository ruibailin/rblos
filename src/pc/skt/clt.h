/*---------------------------
 * clt.h
 *  Created on: Aug 11, 2017
 *      Author: Bailin Rui
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#ifndef SKT_CLT_H_
#define SKT_CLT_H_

extern int rbl_clt_init_skt(int type,char *server_ip,int port);		//type=1:TCP;type=2:UDP
extern void rbl_clt_free_skt(int type,int skt_fd);
extern int rbl_clt_send_skt(int type,int skt_fd,char *frm,int size);
extern int rbl_clt_recv_skt(int type,int skt_fd,char *frm,int size);
extern void rbl_clt_set_nonblock(int type,int skt_fd);
extern void rbl_clt_set_block(int type,int skt_fd);
#endif 
/* end of clt.h */
