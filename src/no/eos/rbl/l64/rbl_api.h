
/*------------------------------------
 * rbl_api.h
 * Create:  2023-02-18
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 * Reduce name pollution when you try to compile an OS
 * Use this API and related lib, you can eliminate the name pollution
 *
 *
 *------------------------------------
 */

#ifndef SRC_RBL_L64_RBL_API_H_
#define SRC_RBL_L64_RBL_API_H_


/*================================================================*/
//file
extern void *rbl_fopen(const char *file, const char *attr);
extern int rbl_feof(void *fp);
extern char *rbl_fgets(void *fp, char *buf, int size);
extern int rbl_fputs(void *fp, const char *s);
extern int rbl_fread(void *fp, void *buf, int size);
extern int rbl_fwrite(void *fp, void *buf, int size);
extern int rbl_fclose(void *fp);

extern int rbl_fseek_set(void *fp, int offset);
extern int rbl_fseek_cur(void *fp, int offset);
extern int rbl_fseek_end(void *fp, int offset);

extern int rbl_lseek_set(int fd, int offset);
extern int rbl_lseek_cur(int fd, int offset);
extern int rbl_lseek_end(int fd, int offset);
extern int rbl_read(int fd, void *buf, int size);
extern int rbl_write(int fd, void *buf, int size);

extern long rbl_get_file_len(int fd);

//memory
extern void rbl_memclr(void *src, int size);
extern void rbl_memcpy(void *src, void *dest, int size);
extern void *rbl_calloc(int cnt, int size);
extern void *rbl_malloc(int size);
extern void rbl_free(void *p);

//print
extern void rbl_puts(const char *s);
extern void rbl_printf(const char *fmt, ...);
#define rbl_print(x...)  	rbl_printf(x);
#define rbl_debug(x...)  	rbl_printf(x);
#define rbl_alarm(x...)   	rbl_printf(x);
#define rbl_panic(x...)		rbl_printf(x);

//string
extern void rbl_strcpy(char *to,const char *from);
extern int 	rbl_strlen(const char *s);
extern char *rbl_strdup (const char *s);
extern int rbl_strcmp(const char *s,const char *d);
extern int rbl_strcasecmp(const char *s,const char *d);
extern int rbl_atoi(const char *s);
extern int rbl_isspace(int c);
extern char *rbl_trim(char *str);

//stream
extern int rbl_open(const char *file,int flag);
extern int rbl_lseek_set(int fd, int offset);
extern int rbl_lseek_cur(int fd, int offset);
extern int rbl_lseek_end(int fd, int offset);
extern int rbl_read(int fd, void *buf, int size);
extern int rbl_write(int fd, void *buf, int size);

//time
extern int rbl_get_sec(void);
extern int rbl_get_usec(void);

extern int rbl_get_second(void);
extern int rbl_get_minute(void);
extern int rbl_get_hour(void);
extern int rbl_get_mday(void);
extern int rbl_get_month(void);
extern int rbl_get_year(void);
extern int rbl_get_wday(void);

extern int rbl_get_rand(void);
/*================================================================*/

#endif 
/* end of rbl_api.h */
