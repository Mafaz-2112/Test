#include "main.h"

/**
 * h_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @i: take a parameter.
 * Return: Flags:
 */
int h_flags(const char *format, int *i)
{
	int g, c_i, flags = 0;
	const char FLAGS_CHAR[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARRAY[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (c_i = *i + 1; format[c_i] != '\0'; c_i++)
	{
		for (g = 0; FLAGS_CHAR[g] != '\0'; g++)
			if (format[c_i] == FLAGS_CHAR[g])
			{
				flags |= FLAGS_ARRAY[g];
				break;
			}

		if (FLAGS_CHAR[g] == 0)
			break;
	}

	*i = c_i - 1;

	return (flags);
}
