#include "eshell.h"

/**
 * cle_inf - initializes info_t struct
 * @inf: struct address
 */
void cle_inf(info_t *inf)
{
	inf->argu = NULL;
	inf->argvu = NULL;
	inf->pth = NULL;
	inf->argcu = 0;
}

/**
 * set_inf - initializes info_t struct
 * @inf: struct address
 * @avc: argument vector
 */
void set_inf(info_t *inf, char **avc)
{
	int in = 0;

	inf->file_name = avc[0];
	if (inf->argu)
	{
		inf->argvu = sttow(inf->argu, " \t");
		if (!inf->argvu)
		{
			inf->argu = malloc(sizeof(char *) * 2);
			if (inf->argvu)
			{
				inf->argvu[0] = _strdup(inf->argu);
				inf->argvu[1] = NULL;
			}
		}
		for (in = 0; inf->argvu && inf->argvu[in]; in++)
			;
		inf->argcu = in;

		rep_ali(inf);
		rep_var(inf);
	}
}

/**
 * fre_inf - frees info_t struct fields
 * @inf: struct address
 * @al: true if freeing all fields
 */
void fre_inf(info_t *inf, int al)
{
	ffre(inf->argvu);
	inf->argvu = NULL;
	inf->pth = NULL;
	if (al)
	{
		if (!inf->cmd_buffer)
			free(inf->argu);
		if (inf->env)
			fre_li(&(inf->env));
		if (inf->history)
			fre_li(&(inf->history));
		if (inf->alias)
			fre_li(&(inf->alias));
		ffre(inf->environ);
			inf->environ = NULL;
		bfre((void **)inf->cmd_buffer);
		if (inf->refd > 2)
			close(inf->refd);
		_putchar(BUF_FLUSH);
	}
}
