/*
 * rbl_os.c
 *
 *  Created on: Apr 13, 2021
 *      Author: steve
 */


#include "0ctr.h"
/*================================================================*/
extern int no_main(int argc, char **argv);

int main(int argc, char **argv)
{
	int ret;
	char *s;

	ret = no_main(argc, argv);

	return ret;
}

/*================================================================*/
/* end of rbl_os.c */
