#include "eshell.h"

/**
 * get_hisf - gets the history file
 * @inf: parameter struct
 *
 * Return: buff
 */

char *get_hisf(info_t *inf)
{
	char *buf, *dir;

	dir = get_envo(inf, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}


/**
 * w_his - creates a file, or appends to an existing file
 * @inf: the parameter struct
 *
 * Return: 1, else -1
 */
int w_his(info_t *inf)
{
	ssize_t f_d;
	char *file_nm = get_hisf(inf);
	list_t *n = NULL;

	if (!file_nm)
		return (-1);

	f_d = open(file_nm, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_nm);
	if (f_d == -1)
		return (-1);
	for (n = inf->history; n; n = n->nxt)
	{
		put_fd(n->st, f_d);
		e_putfd('\n', f_d);
	}
	e_putfd(BUF_FLUSH, f_d);
	close(f_d);
	return (1);
}

/**
 * re_hist - reads history from file
 * @inf: the parameter struct
 *
 * Return: 0 otherwise
 */
int re_his(info_t *inf)
{
	int in, lat = 0, li_coun = 0;
	ssize_t f_d, rd_len, f_size = 0;
	struct stat st;
	char *buff = NULL, *file_nm = get_hisf(inf);

	if (!file_nm)
		return (0);

	f_d = open(file_nm, O_RDONLY);
	free(file_nm);
	if (f_d == -1)
		return (0);
	if (!fstat(f_d, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buff = malloc(sizeof(char) * (f_size + 1));
	if (!buff)
		return (0);
	rd_len = read(f_d, buff, f_size);
	buff[f_size] = 0;
	if (rd_len <= 0)
		return (free(buff), 0);
	close(f_d);
	for (in = 0; in < f_size; in++)
		if (buff[in] == '\n')
		{
			buff[in] = 0;
			bld_hisli(inf, buff + lat, li_coun++);
			lat = in + 1;
		}
	if (lat != in)
		bld_hisli(inf, buff + lat, li_coun++);
	free(buff);
	inf->his = li_coun;
	while (inf->his-- >= HIST_MAX)
		del_natindex(&(inf->history), 0);
	renum_his(inf);
	return (inf->his);
}

/**
 * bld_hisli - adds entry to a history linked list
 * @inf: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @li_coun: the history linecount, histcount
 *
 * Return: 0
 */
int bld_hisli(info_t *inf, char *buff, int li_coun)
{
	list_t *n = NULL;

	if (inf->history)
		n = inf->history;
	ad_nend(&n, buff, li_coun);

	if (!inf->history)
		inf->history = n;
	return (0);
}

/**
 * renum_his - renumbers the history linked list after changes
 * @inf: Structure containing potential arguments. Used to maintain
 *
 * Return: func
 */
int renum_his(info_t *inf)
{
	list_t *n = inf->history;
	int in = 0;

	while (n)
	{
		n->numb = in++;
		n = n->nxt;
	}
	return (inf->his = in);
}
