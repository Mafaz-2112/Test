#include "eshell.h"

/**
 * _strcpy - copies a string
 * @destin: the destination
 * @sor: the source
 *
 * Return: destin
 */
char *_strcpy(char *destin, char *sor)
{
	int in = 0;

	if (destin == sor || sor == 0)
		return (destin);
	while (sor[in])
	{
		destin[in] = sor[in];
		in++;
	}
	destin[in] = 0;
	return (destin);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _strdup - duplicates a string
 * @st: the string to duplicate
 *
 * Return: ret
 */
char *_strdup(const char *st)
{
	int leen = 0;
	char *ret;

	if (st == NULL)
		return (NULL);
	while (*st++)
		leen++;
	ret = malloc(sizeof(char) * (leen + 1));
	if (!ret)
		return (NULL);
	for (leen++; leen--;)
		ret[leen] = *--st;
	return (ret);
}

/**
 * _puts - prints an input string
 * @st: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *st)
{
	int in = 0;

	if (!st)
		return;
	while (st[in] != '\0')
	{
		_putchar(st[in]);
		in++;
	}
}



