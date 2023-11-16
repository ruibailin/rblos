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


#ifndef CLT_H_
#define CLT_H_

extern void app_clt_init_skt(int type);		//type=1:TCP;type=2:UDP
extern void app_clt_free_skt(void);
extern int app_clt_send_skt(char *frm,int size);
extern int app_clt_recv_skt(char *frm,int size);

#endif 
/* end of clt.h */
