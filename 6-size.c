#include "main.h"

/**
 * h_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: Precision.
 */

int h_size(const char *format, int *i)
{
	int size = 0;
    int c_i = *i + 1;

	if (format[curr_i] == 'l')
		size = S_LONG;
	else if (format[c_i] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = c_i - 1;
	else
		*i = c_i;

	return (size);
}
