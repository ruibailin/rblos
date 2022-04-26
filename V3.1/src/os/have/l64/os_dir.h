/*
 * os_dir.h
 *
 *  Created on: Apr 8, 2021
 *      Author: steve
 */

#include "0ctr.h"
#if	_OS_HAVE_L64_
#ifndef SRC_OS_HAVE_L64_OS_DIR_H_
#define SRC_OS_HAVE_L64_OS_DIR_H_
/*================================================================*/
extern int os_dir_exist(char *dir);
extern int os_make_dir(char *dir);
/*================================================================*/
#endif
#endif /* SRC_OS_HAVE_L64_OS_DIR_H_ */
