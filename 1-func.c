#include "main.h"

/************************* 1. *************************/

/**
 * printf_ch - Prints a char
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int printf_cha(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char ch = va_arg(types, int);

	return (handle_write_char(ch, buffer, flags, width, precision, size));
}

/************************* 2. *************************/
/**
 * printf_str - Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int printf_str(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
    char *sr = va_arg(types, char *);
	int leen = 0, i;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (sr == NULL)
	{
		sr = "(null)";
		if (precision >= 6)
			sr = "      ";
	}

	while (sr[leen] != '\0')
		leen++;

	if (precision >= 0 && precision < leen)
		leen = precision;

	if (width > leen)
	{
		if (flags & F_MINUS)
		{
			write(1, &sr[0], leen);
			for (i = width - leen; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - leen; i > 0; i--)
				write(1, " ", 1);
			write(1, &sr[0], leen);
			return (width);
		}
	}

	return (write(1, sr, leen));
}

/************************* 3. *************************/
/**
 * printf_ex_str - Prints ascii codes in hexa of non printable chars
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int printf_ex_str(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = 0, off = 0;
	char *string = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (string == NULL)
		return (write(1, "(null)", 6));

	while (string[a] != '\0')
	{
		if (is_printable(string[a]))
			buffer[a + off] = string[a];
		else
			off += append_hexa_code(string[a], buffer, a + off);

		a++;
	}

	buffer[a + off] = '\0';

	return (write(1, buffer, a + off));
}

/************************* 4. *************************/
/**
 * printf_ine - Print int
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int printf_ine(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	int neg = 0;
	long int i = va_arg(types, long int);
	unsigned long int numb;

	i = con_si_num(size, i);

	if (i == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	numb = (unsigned long int)i;

	if (i < 0)
	{
		numb = (unsigned long int)((-1) * i);
		neg = 1;
	}

	while (numb > 0)
	{
		buffer[a--] = (numb % 10) + '0';
		numb /= 10;
	}

	a++;

	return (write_number(neg, a, buffer, flags, width, precision, size));
}

/************************* 5. *************************/
/**
 * printf_ro13 - Print a string in rot13.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int printf_ro13(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char z,  *string;
	unsigned int a, g;
	char i[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char b[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";
    int cont = 0;

	string = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (string == NULL)
		string = "(AHYY)";
	for (a = 0; string[a]; a++)
	{
		for (g = 0; i[g]; g++)
		{
			if (i[g] == string[a])
			{
				z = b[g];
				write(1, &z, 1);
				cont++;
				break;
			}
		}
		if (!i[g])
		{
			z = string[a];
			write(1, &z, 1);
			cont++;
		}
	}
	return (cont);
}
