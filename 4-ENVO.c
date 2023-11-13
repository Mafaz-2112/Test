#include "eshell.h"

/**
 * my_envo - prints the current environment
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: 0
 */
int my_envo(inf_t *inf)
{
	p_li_string(inf->envo);
	return (0);
}

/**
 * getenvo - gets the value of an environ variable
 * @inf: Structure containing potential arguments. Used to maintain
 * @nm: env var name
 *
 * Return: null
 */
char *getenvo(inf_t *inf, const char *nm)
{
	list_t *n = inf->envo;
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
int my_setenvo(inf_t *inf)
{
	if (inf->argcu != 3)
	{
		e_put("Incorrect number of arguements\n");
		return (1);
	}
	if (set_envo(inf, inf->argvu[1], inf->argvu[2]))
		return (0);
	return (1);
}

/**
 * my_un_setenvo - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: 0
 */
int my_un_setenvo(inf_t *inf)
{
	int in;

	if (inf->argcu == 1)
	{
		e_put("Too few arguements.\n");
		return (1);
	}
	for (in = 1; in <= inf->argcu; in++)
		un_setenv(inf, inf->argvu[in]);

	return (0);
}

/**
 * pop_envo_lis - populates env linked list
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: 0
 */
int pop_envo_lis(inf_t *inf)
{
	list_t *n = NULL;
	size_t in;

	for (in = 0; envoro[in]; in++)
		ad_nend(&n, envoro[in], 0);
	inf->envo = n;
	return (0);
}

