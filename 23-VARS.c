#include "eshell.h"

/**
 * is_cha - test if current char in buffer is a chain delimeter
 * @inf: the parameter struct
 * @buff: the char buffer
 * @pp: address of current position in buf
 *
 * Return: 1, 0 otherwise
 */
int is_cha(info_t *inf, char *buff, size_t *pp)
{
	size_t jj = *pp;

	if (buff[jj] == '|' && buff[jj + 1] == '|')
	{
		buff[jj] = 0;
		jj++;
		inf->cmd_buffer_t = CMD_OR;
	}
	else if (buff[jj] == '&' && buff[jj + 1] == '&')
	{
		buff[jj] = 0;
		jj++;
		inf->cmd_buffer_t = CMD_AND;
	}
	else if (buff[jj] == ';')
	{
		buff[jj] = 0;
		inf->cmd_buffer_t = CMD_CHAIN;
	}
	else
		return (0);
	*pp = jj;
	return (1);
}

/**
 * ch_cha - checks we should continue chaining based on last status
 * @inf: the parameter struct
 * @buff: the char buffer
 * @pp: address of current position in buf
 * @in: starting position in buf
 * @leen: length of buf
 *
 * Return: Void
 */
void ch_cha(info_t *inf, char *buff, size_t *pp, size_t in, size_t leen)
{
	size_t jj = *pp;

	if (inf->cmd_buffer_t == CMD_AND)
	{
		if (inf->stts)
		{
			buff[in] = 0;
			jj = leen;
		}
	}
	if (inf->cmd_buffer_t == CMD_OR)
	{
		if (!inf->stts)
		{
			buff[in] = 0;
			jj = leen;
		}
	}

	*pp = jj;
}

/**
 * rep_ali - replaces an aliases in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1, 0 otherwise
 */
int rep_ali(info_t *inf)
{
	int in;
	list_t *n;
	char *pp;

	for (in = 0; in < 10; in++)
	{
		n = nstar_with(inf->alias, inf->argvu[0], '=');
		if (!n)
			return (0);
		free(inf->argvu[0]);
		pp = _strchr(n->st, '=');
		if (!pp)
			return (0);
		pp = _strdup(pp + 1);
		if (!pp)
			return (0);
		inf->argvu[0] = pp;
	}
	return (1);
}

/**
 * rep_var - replaces vars in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1, 0 otherwise
 */
int rep_var(info_t *inf)
{
	int i = 0;
	list_t *n;

	for (i = 0; inf->argvu[i]; i++)
	{
		if (inf->argvu[i][0] != '$' || !inf->argvu[i][1])
			continue;

		if (!_strcmp(inf->argvu[i], "$?"))
		{
			rep_str(&(inf->argvu[i]),
					_strdup(conv_num(inf->stts, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argvu[i], "$$"))
		{
			rep_str(&(inf->argvu[i]),
					_strdup(conv_num(getpid(), 10, 0)));
			continue;
		}
		n = nstar_with(inf->env, &inf->argvu[i][1], '=');
		if (n)
		{
			rep_str(&(inf->argvu[i]),
					_strdup(_strchr(n->st, '=') + 1));
			continue;
		}
		rep_str(&inf->argvu[i], _strdup(""));

	}
	return (0);
}

/**
 * rep_str - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
