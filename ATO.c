#include "eshell.h"

/**
 * intive - returns true if shell is interactive mode
 * @inf: struct address
 *
 * Return: function
 */
int intive(inf_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->refd <= 2);
}

/**
 * isde - checks if character is a delimeter
 * @ch: the char to check
 * @de: the delimeter string
 * Return: 1
 */
int isde(char ch, char *de)
{
	while (*de)
		if (*de++ == ch)
			return (1);
	return (0);
}

/**
 * is_alpha - checks for alphabetic character
 * @ch: The character to input
 * Return: 1 otherwise 0
 */

int is_alpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * ato - converts a string to an integer
 * @sh: the string to be converted
 * Return: 0
 */

int ato(char *sh)
{
	unsigned int re = 0;
	int in, si = 1, g = 0, out;

	for (in = 0; sh[in] != '\0' && g != 2; in++)
	{
		if (sh[in] == '-')
			si *= -1;

		if (sh[in] >= '0' && sh[in] <= '9')
		{
			g = 1;
			re *= 10;
			re += (sh[in] - '0');
		}
		else if (g == 1)
			g = 2;
	}

	if (si == -1)
		out = -re;
	else
		out = re;

	return (out);
}

