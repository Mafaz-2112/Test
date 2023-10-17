#include "main.h"

/**
 * is_ex - function to E char is printable
 * @c: argument
 *
 * Return:0
 */

int is_ex(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

//===================================================================================//

/**
 * append_code - function to Append ascci in hexadecimal code to buffer
 * @buffer: array
 * @i: argument
 * @ascii_code: ASSCI CODE.
 * Return: 3
 */

int append_code(char asciiCode, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (asciiCode < 0)
		asciiCode *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[asciiCode / 16];
	buffer[i] = map_to[asciiCode % 16];

	return (3);
}

//===================================================================================//

/**
 * isDigit - Verifies if a char is a digit
 * @c: argument
 *
 * Return: 0 
 */

int isDigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);

	return (0);
}

/**
 * co_si_nu - function to Casts a number to the specified size
 * @nu: argumeny
 * @si: argument
 *
 * Return: nu
 */

long int con_si_nu(int size, long int nu)
{
	if (size == S_LONG)
		return (nu);
	else if (size == S_SHORT)
		return ((short)nu);

	return ((int)nu);
}

//===================================================================================//

/**
 * convert_size_unsgnd - function to Casts a number to the specified size
 * @num: argument
 * @size: argument
 *
 * Return: numb
 */

long int con_un_si(unsigned long int numb, int size)
{
	if (size == S_LONG)
		return (numb);
	else if (size == S_SHORT)
		return ((unsigned short)numb);

	return ((unsigned int)numb);
}
