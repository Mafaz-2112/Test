#include "eshell.h"

/**
 * get_envo - returns the string array copy of our environ
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: 0
 */
char **get_envo(info_t *inf)
{
	if (!inf->environ || inf->envo_cha)
	{
		inf->environ = li_str(inf->env);
		inf->envo_cha = 0;
	}

	return (inf->environ);
}

/**
 * un_setenvo - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @varl: the string env var property
 */
int un_setenvo(info_t *inf, char *varl)
{
	list_t *n = inf->env;
	size_t in = 0;
	char *pp;

	if (!n || !varl)
		return (0);

	while (n)
	{
		pp = starts_with(n->st, varl);
		if (pp && *pp == '=')
		{
			inf->envo_cha = del_natindex(&(inf->env), in);
			in = 0;
			n = inf->env;
			continue;
		}
		n = n->nxt;
		in++;
	}
	return (inf->envo_cha);
}

/**
 * set_env - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @varl: the string env var property
 * @val: the string env var value
 *  Return: 0
 */
int set_env(info_t *inf, char *varl, char *val)
{
	char *buff = NULL;
	list_t *n;
	char *pp;

	if (!varl || !val)
		return (0);

	buff = malloc(_strlen(varl) + _strlen(val) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, varl);
	_strcat(buff, "=");
	_strcat(buff, val);
	n = inf->env;
	while (n)
	{
		pp = starts_with(n->st, varl);
		if (pp && *pp == '=')
		{
			free(n->st);
			n->st = buff;
			inf->envo_cha = 1;
			return (0);
		}
		n = n->nxt;
	}
	ad_nend(&(inf->env), buff, 0);
	free(buff);
	inf->envo_cha = 1;
	return (0);
}

