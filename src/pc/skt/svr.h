/*---------------------------
 * svr.h
 *  Created on: Aug 10, 2017
 *      Author: Bailin Rui
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#ifndef SVR_H_
#define SVR_H_

extern void app_svr_init_skt(int type);		//type=1:TCP;type=2:UDP
extern void app_svr_free_skt(void);
extern int app_svr_recv_skt(char *frm,int size);
extern int app_svr_send_skt(char *frm,int size);
#endif 
/* end of svr.h */
