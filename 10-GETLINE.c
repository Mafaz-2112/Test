#include "eshell.h"

/**
 * input_buf - buffers chained commands
 * @inf: parameter struct
 * @buff: address of buffer
 * @leen: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(inf_t *inf, char **buff, size_t *leen)
{
	ssize_t rr = 0;
	size_t leen_pp = 0;

	if (!*leen)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigint_Handler);
#if USE_GETLINE
		rr = get_line(buff, &leen_pp, stdin);
#else
		rr = get_line(inf, buff, &leen_pp);
#endif
		if (rr > 0)
		{
			if ((*buff)[rr - 1] == '\n')
			{
				(*buff)[rr - 1] = '\0';
				rr--;
			}
			inf->licoun_flag = 1;
			rm_comme(*buff);
			bld_hisli(inf, *buff, inf->hiscoun++);
			{
				*leen = rr;
				inf->cmd_buffer = buff;
			}
		}
	}
	return (rr);
}

/**
 * get_inp - gets a line minus the newline
 * @inf: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_inp(inf_t *inf)
{
	static char *buff;
	static size_t in, jj, leen;
	ssize_t rr = 0;
	char **buff_pp = &(inf->argu), *pp;

	_putchar(BUF_FLUSH);
	rr = input_buf(inf, &buff, &leen);
	if (rr == -1)
		return (-1);
	if (leen)
	{
		jj = in;
		pp = buff + in;

		ch_cha(inf, buff, &jj, in, leen);
		while (jj < leen)
		{
			if (is_chn(inf, buff, &jj))
				break;
			jj++;
		}

		in = jj + 1;
		if (in >= leen)
		{
			in = leen = 0;
			inf->cmd_buffer_t = CMD_NORM;
		}

		*buff_pp = pp;
		return (_strlen(pp));
	}

	*buff_pp = buff;
	return (rr);
}

/**
 * read_buf - reads a buffer
 * @inf: parameter struct
 * @buff: buffer
 * @in: size
 *
 * Return: rr
 */
ssize_t read_buf(inf_t *inf, char *buff, size_t *in)
{
	ssize_t rr = 0;

	if (*in)
		return (0);
	rr = read(inf->refd, buff, READ_BUF_SIZE);
	if (rr >= 0)
		*in = rr;
	return (rr);
}

/**
 * get_line - gets the next line of input from STDIN
 * @inf: parameter struct
 * @ptrr: address of pointer to buffer, preallocated or NULL
 * @len: size of preallocated ptr buffer if not NULL
 *
 * Return: ss
 */
int get_line(inf_t *inf, char **ptrr, size_t *len)
{
	static char buff[READ_BUF_SIZE];
	static size_t in, leen;
	size_t kar;
	ssize_t rr = 0, ss = 0;
	char *pp = NULL, *new_pp = NULL, *ch;

	pp = *ptrr;
	if (pp && len)
		ss = *len;
	if (in == leen)
		in = leen = 0;

	rr = read_buf(inf, buff, &leen);
	if (rr == -1 || (rr == 0 && leen == 0))
		return (-1);

	ch = _strchr(buff + in, '\n');
	kar = ch ? 1 + (unsigned int)(ch - buff) : leen;
	new_pp = real_loc(pp, ss, ss ? ss + kar : kar + 1);
	if (!new_pp)
		return (pp ? free(pp), -1 : -1);

	if (ss)
		_strncat(new_pp, buff + in, kar - in);
	else
		_strncpy(new_pp, buff + in, kar - in + 1);

	ss += kar - in;
	in = kar;
	pp = new_pp;

	if (len)
		*len = ss;
	*ptrr = pp;
	return (ss);
}

/**
 * sigint_Handler - blocks ctrl-C
 * @sig_numb: the signal number
 *
 * Return: void
 */
void sigint_Handler(__attribute__((unused))int sig_numb)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
