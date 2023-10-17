#include "main.h"

/**
 * h_precision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */

int h_precision(const char *format, int *i, va_list list)
{
    int precision = -1;
	int c_i = *i + 1;

	if (format[c_i] != '.')
		return (precision);

	precision = 0;

	for (c_i += 1; format[c_i] != '\0'; c_i++)
	{
		if (is_digit(format[c_i]))
		{
			precision *= 10;
			precision += format[c_i] - '0';
		}
		else if (format[c_i] == '*')
		{
			c_i++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = c_i - 1;

	return (precision);
}
