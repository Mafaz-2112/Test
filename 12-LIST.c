#include "eshell.h"

/**
 * ad_n - adds a node to the start of the list
 * @headr: address of pointer to head node
 * @st: str field of node
 * @numb: node index used by history
 *
 * Return: n_h
 */
list_t *ad_n(list_t **headr, const char *st, int numb)
{
	list_t *n_h;

	if (!headr)
		return (NULL);
	n_h = malloc(sizeof(list_t));
	if (!n_h)
		return (NULL);
	mem_set((void *)n_h, 0, sizeof(list_t));
	n_h->numb = numb;
	if (st)
	{
		n_h->st = _strdup(st);
		if (!n_h->st)
		{
			free(n_h);
			return (NULL);
		}
	}
	n_h->nxt = *headr;
	*headr = n_h;
	return (n_h);
}

/**
 * ad_nend - adds a node to the end of the list
 * @headr: address of pointer to head node
 * @st: str field of node
 * @numb: node index used by history
 *
 * Return: n_n
 */
list_t *ad_nend(list_t **headr, const char *st, int numb)
{
	list_t *n_n, *n;

	if (!headr)
		return (NULL);

	n = *headr;
	n_n = malloc(sizeof(list_t));
	if (!n_n)
		return (NULL);
	mem_set((void *)n_n, 0, sizeof(list_t));
	n_n->numb = numb;
	if (st)
	{
		n_n->st = _strdup(st);
		if (!n_n->st)
		{
			free(n_n);
			return (NULL);
		}
	}
	if (n)
	{
		while (n->nxt)
			n = n->nxt;
		n->nxt = n_n;
	}
	else
		*headr = n_n;
	return (n_n);
}

/**
 * p_li_string - prints only the str element of a list_t linked list
 * @hed: pointer to first node
 *
 * Return: in
 */
size_t p_li_string(const list_t *hed)
{
	size_t in = 0;

	while (hed)
	{
		_puts(hed->st ? hed->st : "(nil)");
		_puts("\n");
		hed = hed->nxt;
		in++;
	}
	return (in);
}

/**
 * del_natindex - deletes node at given index
 * @headr: address of pointer to first node
 * @inx: index of node to delete
 *
 * Return: 1, 0 on failure
 */
int del_natindex(list_t **headr, unsigned int inx)
{
	list_t *n, *prev_n;
	unsigned int in = 0;

	if (!headr || !*headr)
		return (0);

	if (!inx)
	{
		n = *headr;
		*headr = (*headr)->nxt;
		free(n->st);
		free(n);
		return (1);
	}
	n = *headr;
	while (n)
	{
		if (in == inx)
		{
			prev_n->nxt = n->nxt;
			free(n->st);
			free(n);
			return (1);
		}
		i++;
		prev_n = n;
		n = nde->nxt;
	}
	return (0);
}

/**
 * fre_li - frees all nodes of a list
 * @headr_ptrr: address of pointer to head node
 *
 * Return: nothing
 */
void fre_li(list_t **headr_ptrr)
{
	list_t *n, *nxt_n, *headr;

	if (!headr_ptrr || !*headr_ptrr)
		return;
	headr = *headr_ptrr;
	n = headr;
	while (n)
	{
		nxt_n = n->nxt;
		free(n->st);
		free(n);
		n = nxt_n;
	}
	*headr_ptrr = NULL;
}

