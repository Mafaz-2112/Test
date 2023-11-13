#include "eshell.h"

/**
 * errato - converts a string to an integer
 * @st: the string to be converted
 * Return: 0 ,otherwise -1 on error
 */
int errato(char *st)
{
	int in = 0;
	unsigned long int res = 0;

	if (*st == '+')
		st++;
	for (in = 0;  st[in] != '\0'; in++)
	{
		if (st[in] >= '0' && st[in] <= '9')
		{
			res *= 10;
			res += (st[in] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * p_error - prints an error message
 * @inf: the parameter & return info struct
 * @est: string containing specified error type
 * Return: 0, otherwise -1 on error
 */
void p_error(inf_t *inf, char *est)
{
	e_puts(inf->file_name);
	e_puts(": ");
	pr_d(inf->li_coun, STDERR_FILENO);
	e_puts(": ");
	e_puts(inf->argvu[0]);
	e_puts(": ");
	e_puts(est);
}

/**
 * pr_d - function prints a decimal (integer) number (base 10)
 * @inp: the input
 * @f_d: the filedescriptor to write to
 *
 * Return: count
 */
int pr_d(int inp, int f_d)
{
	int (*__putchar)(char) = _putchar;
	int in, coun = 0;
	unsigned int _abs, curr;

	if (f_d == STDERR_FILENO)
		__putchar = e_putchar;
	if (inp < 0)
	{
		_abs = -inp;
		__putchar('-');
		coun++;
	}
	else
		_abs = inp;
	curr = _abs;
	for (in = 1000000000; in > 1; in /= 10)
	{
		if (_abs / in)
		{
			__putchar('0' + curr / in);
			coun++;
		}
		curr %= in;
	}
	__putchar('0' + curr);
	coun++;

	return (coun);
}

/**
 * conv_num - converter function, a clone of itoa
 * @numb: number
 * @bases: base
 * @flag: argument flags
 *
 * Return: ptrr
 */
char *conv_num(long int numb, int bases, int flag)
{
	static char *arr;
	static char buffer[50];
	char sign = 0;
	char *ptrr;
	unsigned long na = numb;

	if (!(flag & CONVERT_UNSIGNED) && numb < 0)
	{
		na = -numb;
		sign = '-';

	}
	arr = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptrr = &buffer[49];
	*ptrr = '\0';

	do	{
		*--ptrr = arr[na % bases];
		na /= bases;
	} while (na != 0);

	if (sign)
		*--ptrr = sign;
	return (ptrr);
}

/**
 * rm_comme - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: 0;
 */
void rm_comme(char *buff)
{
	int in;

	for (in = 0; buff[in] != '\0'; in++)
		if (buff[in] == '#' && (!in || buff[in - 1] == ' '))
		{
			buff[in] = '\0';
			break;
		} 
}
