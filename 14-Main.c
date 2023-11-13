#include "eshell.h"

/**
 * main - entry point
 * @ach: arg count
 * @avu: arg vector
 *
 * Return: 0, 1 on error
 */
int main(int ach, char **avu)
{
	inf_t inf[] = { INFO_INIT };
	int f_d = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (f_d)
			: "r" (f_d));

	if (ach == 2)
	{
		f_d = open(avu[1], O_RDONLY);
		if (f_d == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				e_puts(avu[0]);
				e_puts(": 0: Can't open ");
				e_puts(avu[1]);
				e_putchar('\n');
				e_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->refd = f_d;
	}
	pop_envo_lis(inf);
	re_his(inf);
	hsh(inf, avu);
	return (EXIT_SUCCESS);
}

