#include "eshell.h"

/**
 * my_envo - prints the current environment
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: 0
 */
int my_envo(info_t *inf)
{
	pr_li_string(inf->env);
	return (0);
}

/**
 * getenvo - gets the value of an environ variable
 * @inf: Structure containing potential arguments. Used to maintain
 * @nm: env var name
 *
 * Return: null
 */
char *getenvo(info_t *inf, const char *nm)
{
	list_t *n = inf->env;
	char *pp;

	while (n)
	{
		pp = starts_with(n->st, nm);
		if (pp && *pp)
			return (pp);
		n = n->nxt;
	}
	return (NULL);
}

/**
 * my_setenvo - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 0
 */
int my_setenvo(info_t *inf)
{
	if (inf->argcu != 3)
	{
		e_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(inf, inf->argvu[1], inf->argvu[2]))
		return (0);
	return (1);
}

/**
 * my_un_setenvo - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: 0
 */
int my_un_setenvo(info_t *inf)
{
	int in;

	if (inf->argcu == 1)
	{
		e_puts("Too few arguements.\n");
		return (1);
	}
	for (in = 1; in <= inf->argcu; in++)
		un_setenvo(inf, inf->argvu[in]);

	return (0);
}

/**
 * pop_envo_lis - populates env linked list
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: 0
 */
int pop_envo_lis(info_t *inf)
{
	list_t *n = NULL;
	size_t in;

	for (in = 0; environ[in]; in++)
		ad_nend(&n, environ[in], 0);
	inf->env = n;
	return (0);
}
