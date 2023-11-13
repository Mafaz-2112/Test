#ifndef _ESHELL_H_
#define _ESHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include "list_header.h"
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096
extern char **envoro;



/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @argu: a string generated from getline containing arguements
 * @argvu:an array of strings generated from arg
 * @pth: a string path for the current command
 * @argc: the argument count
 * @li_coun: the error count
 * @er_num: the error code for exit()s
 * @licoun_flag: if on count this line of input
 * @file_name: the program filename
 * @envo: linked list local copy of environ
 * @envoro: custom modified copy of environ from LL env
 * @his: the history node
 * @ali: the alias node
 * @envo_cha: on if environ was changed
 * @stts: the return status of the last exec'd command
 * @cmd_buffer: address of pointer to cmd_buf, on if chaining
 * @cmd_buffer_t: CMD_type ||, &&, ;
 * @refd: the fd from which to read line input
 * @hiscoun: the history line number count
 */
typedef struct passinfo
{
	char *argu;
	char **argvu;
	char *pth;
	int argcu;
	unsigned int li_coun;
	int er_nu;
	int licount_flag;
	char *file_name;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **envoro;
	int envo_cha;
	int stts;

	char **cmd_buffer;
	int cmd_buffer_t;
	int refd;
	int his;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/**
 * struct liststr - singly linked list
 * @numb: the number field
 * @st: a string
 * @nxt: points to the next node
 */
typedef struct liststr
{
	int numb;
	char *st;
	struct liststr *nxt;
} list_t;

void e_puts(char *);
int e_putchar(char);
int e_putfd(char ch, int f);
int put_fd(char *string, int f);
int my_exit(info_t *);
int my_cd(info_t *);
int my_help(info_t *);
int intive(info_t *);
int isde(char, char *);
int is_alpha(int);
int ato(char *);
char *getenvo(info_t *, const char *);
int my_envo(info_t *);
int my_setenvo(info_t *);
int my_un_setenvo(info_t *);
int pop_envo_lis(info_t *);
int errato(char *);
void p_error(info_t *, char *);
int pr_d(int, int);
char *conv_num(long int, int, int);
void rm_comme(char *);
char **get_envo(info_t *);
int un_setenvo(info_t *, char *);
int set_env(info_t *, char *, char *);
int my_his(info_t *);
int my_ali(info_t *);
size_t li_leen(const list_t *);
char **li_str(list_t *);
size_t p_li(const list_t *);
list_t *nstar_with(list_t *, char *, char);
ssize_t get_nindex(list_t *, list_t *);
list_t *ad_n(list_t **, const char *, int);
list_t *ad_nend(list_t **, const char *, int);
size_t pr_li_string(const list_t *);
int del_natindex(list_t **, unsigned int);
void fre_li(list_t **);
ssize_t get_inp(info_t *);
int get_line(info_t *, char **, size_t *);
void sigint_Handler(int);
void cle_inf(info_t *);
void set_inf(info_t *, char **);
void fre_inf(info_t *, int);
char *get_hisf(info_t *inf);
int w_his(info_t *inf);
int re_his(info_t *inf);
int bld_hisli(info_t *inf, char *buff, int li_coun);
int renum_his(info_t *inf);
int is_chn(info_t *, char *, size_t *);
void ch_cha(info_t *, char *, size_t *, size_t, size_t);
int rep_ali(info_t *);
int rep_var(info_t *);
int rep_str(char **, char *);
char *mem_set(char *, char, unsigned int);
void ffre(char **);
void *real_loc(void *, unsigned int, unsigned int);
int bfre(void **);
int is_cmnd(info_t *, char *);
char *dup_ch(char *, int, int);
char *find_pth(info_t *, char *, char *);
char **sttow(char *, char *);
char **sttow1(char *, char);
int hsh(info_t *, char **);
int find_bult(info_t *);
void find_cmnd(info_t *);
void fork_cmnd(info_t *);
int loop_hsh(char **);

/**************************/
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

#endif
