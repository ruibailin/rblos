
/*------------------------------------
 * rbl_string.c
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
#include <string.h>
void rbl_strcpy(char *to,const char *from);
void rbl_strcpy(char *to,const char *from)
{
	strcpy(to,from);
}

int rbl_strlen(const char *s);
int rbl_strlen(const char *s)
{
	int i;
	i=strlen(s);
	return i;
}

char *rbl_strdup (const char *s);
char *rbl_strdup (const char *s)
{
	char *d;
	d=strdup(s);
	return d;
}
/*================================================================*/
int rbl_strcmp(const char *s,const char *d);
int rbl_strcmp(const char *s,const char *d)
{
	int i;
	i=strcmp(s,d);
	return i;
}

int rbl_strcasecmp(const char *s,const char *d);
int rbl_strcasecmp(const char *s,const char *d)
{
	int i;
	i=strcasecmp(s,d);
	return i;
}

/*================================================================*/
#include <stdlib.h>
int rbl_atoi(const char *s);
int rbl_atoi(const char *s)
{
	int i;
	i=atoi(s);
	return i;
}

/*================================================================*/
#include <ctype.h>
int rbl_isspace(char c);
int rbl_isspace(char c)
{
	int i;
	i=isspace((int)c);
	return i;
}

/*================================================================*/
char *rbl_trim(char *str);
char *rbl_trim(char *str)
{
    char *s = str;
    char *end;

    /* remove leading spaces/tabs */
    while (rbl_isspace(*s))
        s++;

    /* check for null string */
    if (*s == '\0')
        return s; /* already zero length */

    /* remove trailing spaces and newlines */
    end = s + strlen(s) - 1;
    while (end != s && rbl_isspace(*end))
        end--;
    *(end + 1) = '\0';

    return s;
}

/*================================================================*/

/* end of rbl_string.c */
