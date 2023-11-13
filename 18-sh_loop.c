#include "eshell.h"

/**
 * hsh - main shell loop
 * @inf: the parameter & return info struct
 * @avl: the argument vector from main()
 *
 * Return: 0, 1 on error, or error code
 */
int hsh(inf_t *inf, char **avl)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		cle_inf(inf);
		if (interactive(inf))
			_puts("$ ");
		e_putchar(BUF_FLUSH);
		r = get_inp(inf);
		if (r != -1)
		{
			set_inf(inf, avl);
			builtin_ret = find_bult(inf);
			if (builtin_ret == -1)
				find_cmnd(inf);
		}
		else if (interactive(inf))
			_putchar('\n');
		fre_inf(inf, 0);
	}
	w_his(inf);
	fre_inf(inf, 1);
	if (!interactive(inf) && inf->stts)
		exit(inf->stts);
	if (builtin_ret == -2)
	{
		if (inf->err_num == -1)
			exit(inf->stts);
		exit(inf->err_num);
	}
	return (builtin_ret);
}

/**
 * find_bult - finds a builtin command
 * @inf: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 */
int find_bult(inf_t *inf)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(inf->argvu[0], builtintbl[i].type) == 0)
		{
			inf->li_coun++;
			built_in_ret = builtintbl[i].func(inf);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmnd - finds a command in PATH
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void find_cmnd(inf_t *inf)
{
	char *pth = NULL;
	int i, k;

	inf->pth = inf->argvu[0];
	if (inf->licoun_flag == 1)
	{
		inf->li_conu++;
		inf->licoun_flag = 0;
	}
	for (i = 0, k = 0; inf->argu[i]; i++)
		if (!is_de(inf->argu[i], " \t\n"))
			k++;
	if (!k)
		return;

	pth = find_pth(inf, getenvo(inf, "PATH="), inf->argvu[0]);
	if (pth)
	{
		inf->pth = pth;
		fork_cmnd(inf);
	}
	else
	{
		if ((interactive(inf) || getenvo(inf, "PATH=")
					|| inf->argvu[0][0] == '/') && is_cmnd(inf, inf->argvu[0]))
			fork_cmnd(inf);
		else if (*(inf->argu) != '\n')
		{
			inf->stts = 127;
			p_error(inf, "not found\n");
		}
	}
}

/**
 * fork_cmnd - forks a an exec thread to run cmd
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmnd(inf_t *inf)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{

		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inf->pth, inf->argvu, get_envo(inf)) == -1)
		{
			fre_inf(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(inf->stts));
		if (WIFEXITED(inf->stts))
		{
			inf->stts = WEXITSTATUS(inf->stts);
			if (inf->stts == 126)
				p_error(inf, "Permission denied\n");
		}
	}
}
