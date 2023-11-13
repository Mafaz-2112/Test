#include "eshell.h"

/**
 * e_put - prints an input string
 * @st: the string to be printed
 *
 * Return: NO
 */
void e_put(char *st)
{
	int in = 0;

	if (!st)
		return;
	while (st[in] != '\0')
	{
		e_putchar(st[in]);
		in++;
	}
}

/**
 * e_putchar - writes the character c to stderr
 * @ch: The character to print
 *
 * Return: On success 1
 */
int e_putchar(char ch)
{
	static int in;
	static char buff[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || in >= WRITE_BUF_SIZE)
	{
		write(2, buff, in);
		in = 0;
	}
	if (ch != BUF_FLUSH)
		buff[in++] = ch;
	return (1);
}

/**
 * e_putd - writes the character c to given fd
 * @ch: The character to print
 * @f_d: The filedescriptor to write to
 *
 * Return: On success 1.
 */
int e_putd(char ch, int f_d)
{
	static int in;
	static char buff[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || in >= WRITE_BUF_SIZE)
	{
		write(f_d, buff, in);
		in = 0;
	}
	if (ch != BUF_FLUSH)
		buff[in++] = ch;
	return (1);
}

/**
 * put_fd - prints an input string
 * @st: the string to be printed
 * @f_d: the filedescriptor to write to
 *
 * Return: in
 */
int put_fd(char *st, int f_d)
{
	int in = 0;

	if (!st)
		return (0);
	while (*st)
	{
		in += put_fd(*st++, f_d);
	}
	return (in);
}

