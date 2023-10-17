#include "main.h"
/************** 1. **************/
/**
 * printf_hexal - function to Prints a hexadecimal number in lower or upper
 * @types: arguments
 * @map_to: Array o
 * @buffer: Buffer 
 * @flags:  active flags
 * @flag_ch: flags
 * @width: width
 * @precision: specification
 * @size: specifier
 * @size: specification
 * Return: function
 */
int printf_hexal(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	unsigned long int numb = va_arg(types, unsigned long int),  i_num = numb;

	UNUSED(width);

	numb = con_un_si(numb, size);

	if (numb == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (numb > 0)
	{
		buffer[a--] = map_to[numb % 16];
		numb /= 16;
	}

	if (flags & F_HASH && i_num != 0)
	{
		buffer[a--] = flag_ch;
		buffer[a--] = '0';
	}

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}

/************* 2.  ****************/
/**
 * print_unsigned - function to Prints an unsigned number
 * @types: arguments
 * @buffer: Buffer
 * @flags: flags
 * @width: width
 * @precision: specification
 * @size:specifier
 * Return: function
 */
int printf_un(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	unsigned long int numb = va_arg(types, unsigned long int);

	numb = con_un_si(numb, size);

	if (numb == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (numb > 0)
	{
		buffer[a--] = (numb % 10) + '0';
		numb /= 10;
	}

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}

/************** 3. **************/
/**
 * printf_oct - function to Prints an unsigned number in octal notation
 * @types: arguments
 * @buffer: handle print
 * @flags: flags
 * @width: width
 * @precision: specification
 * @size: specifier
 * Return: function
 */
int printf_oct(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int a = BUFF_SIZE - 2;
	unsigned long int numb = va_arg(types, unsigned long int), i_num = numb;
	
	UNUSED(width);

	numb = con_un_si(numb, size);

	if (numb == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (numb > 0)
	{
		buffer[a--] = (numb % 8) + '0';
		numb /= 8;
	}

	if (flags & F_HASH && i_num != 0)
		buffer[a--] = '0';

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}

/************* 4. **************/
/**
 * printf_hex - function to Prints an unsigned number in hexadecimal notation
 * @types: arguments
 * @buffer: Buffer 
 * @flags: flags
 * @width: width
 * @precision: specification
 * @size: specifier
 * Return: function
 */
int printf_hex(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (printf_hexal(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/************************* 5.*************************/
/**
 * printf_hexU - func to Prints an unsigned number in upper hexadecimal notation
 * @types: arguments
 * @buffer: Buffer
 * @flags: flags
 * @width: width
 * @precision: specification
 * @size: specifier
 * Return: function
 */
int print_hexU(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (printf_hexal(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}
