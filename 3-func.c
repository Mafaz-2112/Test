#include "main.h"

/****************** 1. ******************/
/**
 * printf_poi - function to Prints the value of a pointer variable
 * @types: arguments
 * @buffer: Buffer 
 * @flags: flags
 * @width:  width
 * @precision:  specification
 * @size: specifier
 * Return: function
 */
int printf_poi(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char ex_c = 0, pad = ' ',  map_to[] = "0123456789abcdef";
	int end = BUFF_SIZE - 2, leen = 2, pad_start = 1;  
	void *poi = va_arg(types, void *);
    unsigned long n_poi;

	UNUSED(width);
	UNUSED(size);

	if (poi == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	n_poi = (unsigned long)poi;

	while (n_poi > 0)
	{
		buffer[end--] = map_to[n_poi % 16];
		n_poi /= 16;
		leen++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (flags & F_PLUS)
		ex_c = '+', leen++;
	else if (flags & F_SPACE)
		ex_c = ' ', leen++;

	end++;
	
	return (write_pointer(buffer, end, leen,
		width, flags, pad, ex_c, pad_start));
}

/************************* 2. *************************/

/**
 * printf_bin - function to Prints an unsigned number
 * @types:  arguments
 * @buffer: Buffer 
 * @flags:   active flags
 * @width:  width.
 * @precision: specification
 * @size: specifier
 * Return: cont
 */

int printf_bin(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int cont;
    unsigned int num, mi, a, su, s[32];

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	num = va_arg(types, unsigned int);
	mi = 2147483648; 
	s[0] = num / mi;
	for (a = 1; a < 32; a++)
	{
		mi /= 2;
		s[a] = (num / mi) % 2;
	}
	for (a = 0, su = 0, cont = 0; a < 32; a++)
	{
		su += s[a];
		if (su || a == 31)
		{
			char z = '0' + s[a];

			write(1, &z, 1);
			cont++;
		}
	}
	return (cont);
}

/************************* 3. *************************/
/**
 * print_reverse - function to Prints reverse string.
 * @types: arguments
 * @buffer: Buffer 
 * @flags: active flags
 * @width: width
 * @precision: specification
 * @size: specifier
 * Return: cont
 */

int printf_re(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a, cont = 0;
	char *s;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	s = va_arg(types, char *);

	if (s == NULL)
	{
		UNUSED(precision);

		s = ")Null(";
	}
	for (a = 0; s[a]; a++)
		;

	for (a = a - 1; a >= 0; a--)
	{
		char Z = s[a];

		write(1, &Z, 1);
		cont++;
	}
	return (cont);
}
/************************* 4. *************************/

/**
 * printf_37 - function to Prints a percent sign
 * @types: arguments
 * @buffer: Buffer 
 * @flags: active flags
 * @width: width.
 * @precision: specification
 * @size: specifier
 * Return: function
 */
int printf_37(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}
