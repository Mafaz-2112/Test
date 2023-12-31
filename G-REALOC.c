#include "eshell.h"

/**
 * mem_set - fills memory with a constant byte
 * @sh: the pointer to the memory area
 * @bs: the byte to fill *s with
 * @ni: the amount of bytes to be filled
 * Return: sh
 */
char *mem_set(char *sh, char bs, unsigned int ni)
{
	unsigned int in;

	for (in = 0; in < ni; in++)
		sh[in] = bs;
	return (sh);
}

/**
 * ffre - frees a string of strings
 * @pp: string of strings
 */
void ffre(char **pp)
{
	char **ae = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(ae);
}


/**
 * real_loc - reallocates a block of memory
 * @ptrr: pointer to previous malloc'ated block
 * @old_s: byte size of previous block
 * @new_s: byte size of new block
 *
 * Return: pp
 */
void *real_loc(void *ptrr, unsigned int old_s, unsigned int new_s)
{
	char *pp;

	if (!ptrr)
		return (malloc(new_s));
	if (!new_s)
		return (free(ptrr), NULL);
	if (new_s == old_s)
		return (ptrr);

	pp = malloc(new_s);
	if (!pp)
		return (NULL);

	old_s = old_s < new_s ? old_s : new_s;
	while (old_s--)
		pp[old_s] = ((char *)ptrr)[old_s];
	free(ptrr);
	return (pp);
}
