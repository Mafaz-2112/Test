#include "eshell.h"

/**
 * bfre - frees a pointer and NULLs the address
 * @ptrr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfre(void **ptrr)
{
	if (ptrr && *ptrr)
	{
		free(*ptrr);
		*ptrr = NULL;
		return (1);
	}
	return (0);
}
