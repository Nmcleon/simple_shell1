#include "shell.h"

/**
 * is_cmd - determines whether a file is an executable command
 *
 * @info: info struct
 * @path: path to file
 *
 * Return: 1, if true
 * else, 0
 */

int is_cmd(info_t *info, char *path)
{
	struct stat t;

	(void)info;
	if (!path || stat(path, &t))
		return (0);

	if (t.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates x-ters
 *
 * @pathstr: PATH string
 * @start: initial index
 * @stop: final index
 *
 * Return: pointer to some new buffer
 */

char *dup_chars(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int i = 0, j = 0;

	for (j = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buff[j++] = pathstr[i];
	buff[j] = 0;
	return (buff);
}

/**
 * find_path - finds command in PATH string
 *
 * @info: info struct
 * @pathstr: PATH string
 * @cmd: command to find
 *
 * Return: full path of command
 * else, NULL
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, cpos = 0;
	char *pth;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			pth = dup_chars(pathstr, cpos, i);
			if (!*pth)
				_strcat(pth, cmd);
			else
			{
				_strcat(pth, "/");
				_strcat(pth, cmd);
			}
			if (is_cmd(info, pth))
				return (pth);
			if (!pathstr[i])
				break;
			cpos = i;
		}
		i++;
	}
	return (NULL);
}
