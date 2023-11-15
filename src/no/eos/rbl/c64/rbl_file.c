
/*------------------------------------
 * rbl_file.c
 * Create:  2023-02-18
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */

#include "1imp.h"

/*================================================================*/
#include <stdio.h>

void *rbl_fopen(const char *file,const char *attr)
{
	FILE *fp;

	if (file==NULL)
    	return NULL;

	fp = fopen(file, attr);
	return (void *)fp;
}

int rbl_feof(void *fp);
int rbl_feof(void *fp)
{
	int i;
	i=feof((FILE *)fp);
	return i;
}

char *rbl_fgets(void *fp, char *buf, int size);
char *rbl_fgets(void *fp, char *buf, int size)
{
	char *s;
    if (fp==NULL)
    	return NULL;

    s=fgets(buf, size, (FILE *)fp);
    return s;
}

int rbl_fread(void *fp, void *buf, int size);
int rbl_fread(void *fp, void *buf, int size)
{
	int len;
    if (fp==NULL)
    	return -1;

    len=fread(buf, 1, size, (FILE *)fp);
    return len;
}

int rbl_fputs(void *fp, const char *s);
int rbl_fputs(void *fp, const char *s)
{
	int len;
    if (fp==NULL)
    	return -1;

    len=fputs(s, (FILE *)fp);
    return len;
}

int rbl_fwrite(void *fp, void *buf, int size);
int rbl_fwrite(void *fp, void *buf, int size)
{
	int len;
    if (fp==NULL)
    	return -1;

    len=fwrite(buf, 1, size, (FILE *)fp);
    return len;
}

int rbl_fclose(void *fp);
int rbl_fclose(void *fp)
{
	int len;
    if (fp==NULL)
    	return -1;

    len=fclose(fp);
    return len;
}

/*================================================================*/
#include <unistd.h>
int rbl_fseek_set(void *fp, int offset);
int rbl_fseek_set(void *fp, int offset)
{
	int i;
	i=fseek((FILE *)fp, (long int)offset, SEEK_SET);
	return i;
}

int rbl_fseek_cur(void *fp, int offset);
int rbl_fseek_cur(void *fp, int offset)
{
	int i;
	i=fseek((FILE *)fp, (long int)offset, SEEK_CUR);
	return i;
}

int rbl_fseek_end(void *fp, int offset);
int rbl_fseek_end(void *fp, int offset)
{
	int i;
	i=fseek((FILE *)fp, (long int)offset, SEEK_END);
	return i;
}

/*================================================================*/
#include <sys/stat.h>
long rbl_get_file_len(int fd);
long rbl_get_file_len(int fd)
{
    struct stat st;
    fstat(fd, &st);
    return (st.st_size);
}

/*================================================================*/

/* end of rbl_file.c */
