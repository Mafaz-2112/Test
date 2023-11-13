#include "eshell.h"

/**
 * _strlen - returns the length of a string
 * @sh: the string whose length to check
 *
 * Return: in
 */
int _strlen(char *sh)
{
	int in = 0;

	if (!sh)
		return (0);

	while (*sh++)
		in++;
	return (in);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @st1: the first strang
 * @st2: the second strang
 *
 * Return: n
 */
int _strcmp(char *st1, char *st2)
{
	while (*st1 && *st2)
	{
		if (*st1 != *st2)
			return (*st1 - *st2);
		st1++;
		st2++;
	}
	if (*st1 == *st2)
		return (0);
	else
		return (*st1 < *st2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @destin: the destination buffer
 * @sor: the source buffer
 *
 * Return: ret
 */
char *_strcat(char *destin, char *sor)
{
	char *ret = destin;

	while (*destin)
		destin++;
	while (*sor)
		*destin++ = *sor++;
	*destin = *sor;
	return (ret);
}

