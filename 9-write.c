#include "main.h"

/**************************************************/

/**
 * handle_write_char - function to  Prints a string
 * @c: types.
 * @buffer: Buffer 
 * @flags: flags.
 * @width: width.
 * @precision: specifier
 * @size: Sspecifier
 *
 * Return: function
 */

int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	
	char pad = ' ';
    int a = 0;
	UNUSED(precision), UNUSED(size);

	if (flags & F_ZERO)
		pad = '0';

	buffer[a++] = c;
	buffer[a] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (a = 0; a < width - 1; a++)
			buffer[BUFF_SIZE - a - 2] = pad;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - a - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - a - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**************************************************/

/**
 * write_number - function to Prints a string
 * @is_negative: arguments
 * @ind: types.
 * @buffer: buffer
 * @flags: flags
 * @width: width.
 * @precision: specifier
 * @size: specifier
 *
 * Return: func
 */

int write_number(int is_negative, int end, char buffer[],
	int flags, int width, int precision, int size)
{
	int leen = BUFF_SIZE - end - 1;
	char pad = ' ', ex_c = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (is_negative)
		ex_c = '-';
	else if (flags & F_PLUS)
		ex_c = '+';
	else if (flags & F_SPACE)
		ex_c = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		leen, pad, ex_c));
}

/**************************************************/

/**
 * write_num - function to Write a number using a bufffer
 * @end: index buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec:  specifier
 * @length: length
 * @pad: Pading charcter
 * @ex_c: Extra charcter
 *
 * Return: function
 */

int write_num(int end, char buffer[],
	int flags, int width, int prec,
	int length, char pad, char ex_c)
{
	int i, pad_start = 1;

	if (prec == 0 && end == BUFF_SIZE - 2 && buffer[end] == '0' && width == 0)
		return (0); 
	if (prec == 0 && end == BUFF_SIZE - 2 && buffer[end] == '0')
		buffer[end] = pad = ' '; 
	if (prec > 0 && prec < length)
		pad = ' ';
	while (prec > length)
		buffer[--end] = '0', length++;
	if (ex_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = pad;
		buffer[i] = '\0';
		if (flags & F_MINUS && pad == ' ')
		{
			if (ex_c)
				buffer[--end] = ex_c;
			return (write(1, &buffer[end], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && pad == ' ')
		{
			if (ex_c)
				buffer[--end] = ex_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[end], length));
		}
		else if (!(flags & F_MINUS) && pad == '0')
		{
			if (ex_c)
				buffer[--pad_start] = ex_c;
			return (write(1, &buffer[pad_start], i - pad_start) +
				write(1, &buffer[end], length - (1 - pad_start)));
		}
	}
	if (ex_c)
		buffer[--end] = ex_c;
	return (write(1, &buffer[end], length));
}

/**************************************************/

/**
 * write_unsgnd - functio to Writes an unsigned number
 * @is_ne: num is negative
 * @end: I starts in the buffer
 * @buffer: Array 
 * @flags:  specifiers
 * @width: specifier
 * @precision: specifier
 * @size: specifier
 *
 * Return: function
 */

int write_unsgnd(int is_ne, int end,
	char buffer[],
	int flags, int width, int precision, int size)
{
	int leen = BUFF_SIZE - end - 1, i = 0;
	char pad = ' ';

	UNUSED(is_ne);
	UNUSED(size);

	if (precision == 0 && end == BUFF_SIZE - 2 && buffer[end] == '0')
		return (0);

	if (precision > 0 && precision < leen)
		pad = ' ';

	while (precision > leen)
	{
		buffer[--end] = '0';
		leen++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';

	if (width > length)
	{
		for (i = 0; i < width - leen; i++)
			buffer[i] = pad;

		buffer[i] = '\0';

		if (flags & F_MINUS) 
		{
			return (write(1, &buffer[end], leen) + write(1, &buffer[0], i));
		}
		else 
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[end], leen));
		}
	}

	return (write(1, &buffer[end], leen));
}

/**************************************************/

/**
 * write_pointer - function to Write a memory address
 * @buffer: Arrays 
 * @end: Index at starts in the buffer
 * @length: Length 
 * @width: specifier
 * @flags:specifier
 * @pad: representing the padding
 * @ex_c: extra char
 * @pad_start: Index padding should start
 *
 * Return: function
 */

int write_pointer(char buffer[], int end, int leen,
	int width, int flags, char pad, char ex_c, int pad_start)
{
	int i;

	if (width > leen)
	{
		for (i = 3; i < width - leen + 3; i++)
			buffer[i] = pad;
		buffer[i] = '\0';
		if (flags & F_MINUS && pad == ' ')
		{
			buffer[--end] = 'x';
			buffer[--end] = '0';
			if (ex_c)
				buffer[--end] = ex_c;
			return (write(1, &buffer[end], leen) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && pad == ' ')
		{
			buffer[--end] = 'x';
			buffer[--end] = '0';
			if (ex_c)
				buffer[--end] = ex_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[end], leen));
		}
		else if (!(flags & F_MINUS) && pad == '0')
		{
			if (ex_c)
				buffer[--pad_start] = ex_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[pad_start], i - pad_start) +
				write(1, &buffer[end], leen - (1 - pad_start) - 2));
		}
	}
	buffer[--end] = 'x';
	buffer[--end] = '0';
	if (ex_c)
		buffer[--end] = ex_c;
	return (write(1, &buffer[end], BUFF_SIZE - end - 1));
}
