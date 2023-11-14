/* ZXJ10.H
   Copyright(c) 1993-1997. (ZTE)Shenzhen Zhongxing New Telecom Equip. Co. Ltd.
   Research Institute of Nanjing Zhongxing New Telecom.
   All rights reserved. */

#ifndef __ZXTYPE_H
#define __ZXTYPE_H

#define INIT_STATE                 (WORD)0     /* process initial state */

#define TIMER1                     (BYTE)0
#define TIMER2                     (BYTE)1
#define TIMER3                     (BYTE)2
#define TIMER4                     (BYTE)3
#define TIMER5                     (BYTE)4
#define TIMER6                     (BYTE)5
#define TIMER7                     (BYTE)6
#define TIMER8                     (BYTE)7

#define R01_SLAVE                  (WORD)0
#define R01_MASTER                 (WORD)1

#define R01_SUCCESS                (WORD)0
#define R01_OTHER_ERROR            (WORD)1
#define R01_PNO_ERROR              (WORD)2
#define R01_NOSUPPORT              (WORD)3

#define R01_MPCOMM_ABORT           (WORD)4
#define R01_MPCOMM_OVERRLOAD       (WORD)5
#define R01_PPCOMM_ABORT           (WORD)6
#define R01_PPCOMM_OVERRLOAD       (WORD)7
#define R01_MATECOMM_ABORT         (WORD)8
#define R01_MATECOMM_OVERRLOAD     (WORD)9

#define SEND_MSG_TO_MP             (BYTE)0
#define SEND_MSG_TO_SELF           (BYTE)2
#define SEND_MSG_TO_MATE           (BYTE)0x82
#endif
