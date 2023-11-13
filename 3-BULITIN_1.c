#include "eshell.h"

/**
 * my_his - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return:  0
 */
int my_his(inf_t *inf)
{
	p_li(inf->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @inf: parameter struct
 * @st: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(inf_t *inf, char *st)
{
	char *pp, ch;
	int rets;

	pp = _strchr(st, '=');
	if (!pp)
		return (1);
	ch = *pp;
	*pp = 0;
	rets = del_natindex(&(inf->alias),
		get_nindex(inf->alias, nstar_with(inf->alias, st, -1)));
	*pp = ch;
	return (rets);
}

/**
 * set_alias - sets alias to string
 * @inf: parameter struct
 * @st: the string alias
 *
 * Return:  0 , 1 on error
 */
int set_alias(inf_t *inf, char *st)
{
	char *pp;

	pp = _strchr(st, '=');
	if (!pp)
		return (1);
	if (!*++pp)
		return (unset_alias(inf, st));

	unset_alias(inf, st);
	return (ad_nend(&(inf->ali), st, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @n: the alias node
 *
 * Return: 0, 1 on error
 */
int print_alias(list_t *n)
{
	char *pp = NULL, *ai = NULL;

	if (n)
	{
		pp = _strchr(n->st, '=');
		for (ai = n->st; ai <= pp; ai++)
		_putchar(*ai);
		_putchar('\'');
		_puts(pp + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return:  0
 */
int _myalias(inf_t *inf)
{
	int in = 0;
	char *pp = NULL;
	list_t *n = NULL;

	if (inf->argcu == 1)
	{
		n = inf->ali;
		while (n)
		{
			print_alias(n);
			n = n->nxt;
		}
		return (0);
	}
	for (in = 1; inf->argvu[in]; in++)
	{
		pp = _strchr(inf->argvu[in], '=');
		if (pp)
			set_alias(inf, inf->argvu[in]);
		else
			print_alias(nstar_with(inf->ali, inf->argvu[in], '='));
	}

	return (0);
}
