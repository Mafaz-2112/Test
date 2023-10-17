#include "main.h"

/**
 * h_width - function to Calculates the width for printing
 * @format: Formatted  arguments.
 * @i: List of arguments 
 * @list: list of arguments
 *
 * Return: width.
 */
int h_width(const char *format, int *i, va_list list)
{
	
	int width = 0;
    int c_i;
    
	for (c_i = *i + 1; format[c_i] != '\0'; c_i++)
	{
		if (isDigit(format[c_i]))
		{
			width *= 10;
			width += format[c_i] - '0';
		}
		else if (format[c_i] == '*')
		{
			c_i++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = c_i - 1;

	return (width);
}
