#include "main.h"
/**
 * h_printf - func to Prints an argument based on its type
 * @fmt: arguments.
 * @list: arguments to be printed.
 * @end: end.
 * @buffer: Buffer 
 * @flags: C flags
 * @width: width.
 * @precision:  specification
 * @size: specifier
 * Return: 1 or 2..
 */
int h_printf(const char *ft, int *end, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, leen = 0, pchars = -1;
	match f_t[] = {
		{'c', printf_cha}, {'s', printf_str}, {'%', printf_37},
		{'i', printf_ine}, {'d', printf_ine}, {'b', printf_bin},
		{'u', printf_un}, {'o', printf_oct}, {'x', printf_hex},
		{'X', printf_hexU}, {'p', printf_poi}, {'S', printf_ex_str},
		{'r', printf_re}, {'R', printf_ro13}, {'\0', NULL}
	};
	for (i = 0; f_t[i].ft != '\0'; i++)
		if (ft[*end] == f_t[i].ft)
			return (f_t[i].fn(list, buffer, flags, width, precision, size));

	if (f_t[i].ft == '\0')
	{
		if (ft[*end] == '\0')
			return (-1);
		leen += write(1, "%%", 1);
		if (ft[*end - 1] == ' ')
			leen += write(1, " ", 1);
		else if (width)
		{
			--(*end);
			while (ft[*end] != ' ' && ft[*end] != '%')
				--(*execve);
			if (ft[*end] == ' ')
				--(*end);
			return (1);
		}
		leen += write(1, &ft[*end], 1);
		return (leen);
	}
	return (pchars);
}
