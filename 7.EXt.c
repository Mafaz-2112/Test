#include "eshell.h"

/**
 **_strncpy - copies a string
 *@destin: the destination string to be copied to
 *@sor: the source string
 *@na: the amount of characters to be copied
 *Return: st
 */
char *_strncpy(char *destin, char *sor, int na)
{
	int in, jj;
	char *st = destin;

	in = 0;
	while (sor[in] != '\0' && in < na - 1)
	{
		destin[in] = sor[in];
		in++;
	}
	if (in < na)
	{
		jj = in;
		while (jj < na)
		{
			destin[jj] = '\0';
			jj++;
		}
	}
	return (st);
}

/**
 **_strncat - concatenates two strings
 *@destin: the first string
 *@sor: the second string
 *@na: the amount of bytes to be maximally used
 *Return: st
 */
char *_strncat(char *destin, char *sor, int na)
{
	int in, jj;
	char *st = destin;

	in = 0;
	jj = 0;
	while (destin[in] != '\0')
		in++;
	while (sor[jj] != '\0' && jj < na)
	{
		destin[in] = sor[jj];
		in++;
		jj++;
	}
	if (jj < na)
		destin[in] = '\0';
	return (st);
}

/**
 **_strchr - locates a character in a string
 *@st: the string to be parsed
 *@ch: the character to look for
 *Return: st
 */
char *_strchr(char *st, char ch)
{
	do {
		if (*st == ch)
			return (st);
	} while (*st++ != '\0');

	return (NULL);
}
