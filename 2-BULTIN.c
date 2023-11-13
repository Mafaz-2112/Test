#include "eshell.h"

/**
 * my_exit - exits the shell
 * @inf: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 0
 */
int my_exit(info_t *inf)
{
	int ex;

	if (inf->argvu[1])
	{
		ex = errato(inf->argvu[1]);
		if (ex == -1)
		{
			inf->stts = 2;
			p_error(inf, "Illegal number: ");
			e_puts(inf->argvu[1]);
			e_putchar('\n');
			return (1);
		}
		inf->er_nu = errato(inf->argvu[1]);
		return (-2);
	}
	inf->er_nu = -1;
	return (-2);
}

/**
 * my_cd - changes the current directory of the process
 * @inf: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return:  0
 */
int my_cd(info_t *inf)
{
	char *st, *dirct, buffer[1024];
	int cdir_re;

	st = getcwd(buffer, 1024);
	if (!st)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argvu[1])
	{
		dirct = getenvo(inf, "HOME=");
		if (!dirct)
			cdir_re =
				chdir((dirct = getenvo(inf, "PWD=")) ? dirct : "/");
		else
			cdir_re = chdir(dirct);
	}
	else if (_strcmp(inf->argvu[1], "-") == 0)
	{
		if (!getenvo(inf, "OLDPWD="))
		{
			_puts(st);
			_putchar('\n');
			return (1);
		}
		_puts(getenvo(inf, "OLDPWD=")), _putchar('\n');
		cdir_re =
			chdir((dirct = getenvo(inf, "OLDPWD=")) ? dirct : "/");
	}
	else
		cdir_re = chdir(inf->argvu[1]);
	if (cdir_re == -1)
	{
		p_error(inf, "can't cd to ");
		e_puts(inf->argvu[1]), e_putchar('\n');
	}
	else
	{
		set_env(inf, "OLDPWD", getenvo(inf, "PWD="));
		set_env(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_help - changes the current directory of the process
 * @inf: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 0
 */

int my_help(info_t *inf)
{
	char **argu_arr;

	argu_arr = inf->argvu;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argu_arr);
	return (0);
}

