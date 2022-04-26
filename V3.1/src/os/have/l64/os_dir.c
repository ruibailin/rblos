/*
 * os_dir.c
 *
 *  Created on: Apr 8, 2021
 *      Author: steve
 */


#include "0ctr.h"
#if	_OS_HAVE_L64_
/*================================================================*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "os_print.h"
int os_dir_exist(char *dir);
int os_dir_exist(char *dir)
{
	int ret;
	ret = access(dir, F_OK);
	if(ret == 0)
		return 1;
	else
		return 0;
}

int os_make_dir(char *dir);
int os_make_dir(char *dir)
{
	int ret;
	ret = mkdir(dir,0755);
	if(ret == -1)
	{
		os_debug("mkdir   error:%s\n",dir);
		ret = 0;
	}
	else
		ret = 1;
	return ret;
}

/*================================================================*/
#endif
/* end of os_dir.c */
