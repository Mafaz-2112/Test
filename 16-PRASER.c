#include "eshell.h"

/**
 * is_cmnd - determines if a file is an executable command
 * @inf: the info struct
 * @pth: path to the file
 *
 * Return: 1, 0 otherwise
 */
int is_cmnd(info_t *inf, char *pth)
{
	struct stat stt;

	(void)inf;
	if (!pth || stat(pth, &stt))
		return (0);

	if (stt.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_ch - duplicates characters
 * @pthstr: the PATH string
 * @star: starting index
 * @sop: stopping index
 *
 * Return: buf
 */
char *dup_ch(char *pthstr, int star, int sop)
{
	static char buf[1024];
	int in = 0, ka = 0;

	for (ka = 0, in = star; in < sop; in++)
		if (pthstr[in] != ':')
			buf[ka++] = pthstr[in];
	buf[ka] = 0;
	return (buf);
}

/**
 * find_pth - finds this cmd in the PATH string
 * @inf: the info struct
 * @pthstr: the PATH string
 * @cmnd: the cmd to find
 *
 * Return: nothing
 */
char *find_pth(info_t *inf, char *pthstr, char *cmnd)
{
	int in = 0, curr_pos = 0;
	char *pth;

	if (!pthstr)
		return (NULL);
	if ((_strlen(cmnd) > 2) && starts_with(cmnd, "./"))
	{
		if (is_cmnd(inf, cmnd))
			return (cmnd);
	}
	while (1)
	{
		if (!pthstr[in] || pthstr[in] == ':')
		{
			pth = dup_ch(pthstr, curr_pos, in);
			if (!*pth)
				_strcat(pth, cmnd);
			else
			{
				_strcat(pth, "/");
				_strcat(pth, cmnd);
			}
			if (is_cmnd(inf, pth))
				return (pth);
			if (!pthstr[in])
				break;
			curr_pos = in;
		}
		in++;
	}
	return (NULL);
}

