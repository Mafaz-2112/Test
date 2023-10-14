#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int a, p = 0, p_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list ls;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(ls, format);

	for (a = 0; format && format[a] != '\0'; a++)
	{
		if (format[a] != '%')
		{
			buffer[buff_ind++] = format[a];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[a], 1);*/
			p_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &a);
			width = get_width(format, &a, ls);
			precision = get_precision(format, &a, ls);
			size = get_size(format, &a);
			++a;
			p = handle_print(format, &a, ls, buffer,
				flags, width, precision, size);
			if (p == -1)
				return (-1);
			p_chars += p;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(ls);

	return (p_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
