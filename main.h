#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct ft - Struct op
 *
 * @ft: The format.
 * @fn: The function associated.
 */
struct ft
{
	char ft;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct ft match - Struct op
 *
 * @ft: The format.
 * @match: The function associated.
 */
typedef struct ft match;

int _printf(const char *format, ...);
int h_printf(const char *ft, int *i,
va_list list, char buffer[], int flags, int width, int precision, int size);

/****************** function ******************/

int _putchar(char c);
int printf_cha(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printf_str(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printf_37(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printf_ine(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printf_bin(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printf_un(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printf_oct(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printf_hex(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printf_hexU(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printf_hexal(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);
int printf_ex_str(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printf_poi(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printf_re(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printf_ro13(va_list types, char buffer[],
	int flags, int width, int precision, int size); 

//============================================================================//

int h_flags(const char *format, int *i);
int h_width(const char *format, int *i, va_list list);
int h_precision(const char *format, int *i, va_list list);
int h_size(const char *format, int *i);

//============================================================================//

int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size);
int write_number(int is_positive, int end, char buffer[],
	int flags, int width, int precision, int size);
int write_num(int end, char bff[], int flags, int width, int precision,
	int leen, char pad, char ex_c);
int write_pointer(char buffer[], int end, int leen,
	int width, int flags, char pad, char ex_c, int pad_start);

int write_unsgnd(int is_neg, int end,
char buffer[],
	int flags, int width, int precision, int size);

/****************** ut ******************/

int is_ex(char);
int append_code(char, char[], int);
int isDigit(char);

long int con_si_nu(int size, long int nu);
long int con_un_si(unsigned long int numb, int size);

#endif 
