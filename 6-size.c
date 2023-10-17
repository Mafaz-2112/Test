#include "main.h"

/**
 * h_size - function to Calculates the size to cast the argument
 * @format: Formatted arguments
 * @i: arguments to be printed.
 *
 * Return: Precision.
 */

int h_size(const char *format, int *i)
{
	int size = 0;
    int c_i = *i + 1;

	if (format[c_i] == 'l')
		size = S_LONG;
	else if (format[c_i] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = c_i - 1;
	else
		*i = c_i;

	return (size);
}
