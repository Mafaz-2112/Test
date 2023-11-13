#include "eshell.h"

/**
 * li_leen - determines length of linked list
 * @hed: pointer to first node
 *
 * Return: in
 */
size_t li_leen(const list_t *hed)
{
	size_t in = 0;

	while (hed)
	{
		hed = hed->nxt;
		in++;
	}
	return (in);
}

/**
 * li_str - returns an array of strings of the list->str
 * @headr: pointer to first node
 *
 * Return: sts
 */
char **li_str(list_t *headr)
{
	list_t *n = headr;
	size_t in = li_leen(headr), jj;
	char **sts;
	char *st;

	if (!headr || !in)
		return (NULL);
	sts = malloc(sizeof(char *) * (in + 1));
	if (!sts)
		return (NULL);
	for (in = 0; n; n = n->nxt, in++)
	{
		st = malloc(_strlen(n->st) + 1);
		if (!st)
		{
			for (jj = 0; jj < in; jj++)
				free(sts[jj]);
			free(sts);
			return (NULL);
		}

		st = _strcpy(st, n->st);
		sts[in] = st;
	}
	sts[in] = NULL;
	return (sts);
}


/**
 * pr_li - print all elements of a list_t linked list
 * @hed: pointer to first node
 *
 * Return: in
 */
size_t pr_li(const list_t *hed)
{
	size_t in = 0;

	while (hed)
	{
		_puts(conv_num(hed->numb, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hed->st ? hed->st : "(nil)");
		_puts("\n");
		hed = hed->nxt;
		in++;
	}
	return (in);
}

/**
 * nstar_with - returns node whose string starts with prefix
 * @n: pointer to list head
 * @pfix: string to match
 * @ch: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *nstar_with(list_t *n, char *pfix, char ch)
{
	char *pp = NULL;

	while (n)
	{
		pp = starts_with(n->st, pfix);
		if (pp && ((ch == -1) || (*pp == ch)))
			return (n);
		n = n->nxt;
	}
	return (NULL);
}

/**
 * get_nindex - gets the index of a node
 * @headr: pointer to list head
 * @n: pointer to the node
 *
 * Return: -1
 */
ssize_t get_nindex(list_t *headr, list_t *n)
{
	size_t in = 0;

	while (headr)
	{
		if (headr == n)
			return (in);
		headr = headr->nxt;
		in++;
	}
	return (-1);
}

