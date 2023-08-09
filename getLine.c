#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: the eter struct
 * @buf: the ess of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t s = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		s = getline(buf, &len_p, stdin);
#else
		s = _getline(info, buf, &len_p);
#endif
		if (s > 0)
		{
			if ((*buf)[s - 1] == '\n')
			{
				(*buf)[s - 1] = '\0';
				s--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = s;
				info->cmd_buf = buf;
			}
		}
	}
	return (s);
}

/**
 * get_input - gets line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t j, k, le;
	ssize_t s = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	s = input_buf(info, &buf, &le);
	if (s == -1)
		return (-1);
	if (le)
	{
		k = j;
		p = buf + j;
		check_chain(info, buf, &k, j, le);
		while (k < le)
		{
			if (is_chain(info, buf, &k))
				break;
			k++;
		}

		j = k + 1;
		if (j >= le)
		{
			j = le = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (s);
}

/**
 * read_buf - reads buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: s (Success)
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t s = 0;

	if (*i)
		return (0);
	s = read(info->readfd, buf, READ_BUF_SIZE);
	if (s >= 0)
		*i = s;
	return (s);
}

/**
 * _getline - gets next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: t
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t l;
	ssize_t r = 0, t = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		t = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	l = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, t, t ? t + l : l + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (t)
		_strncat(new_p, buf + i, l - i);
	else
		_strncpy(new_p, buf + i, l - i + 1);

	t += l - i;
	i = l;
	p = new_p;

	if (length)
		*length = t;
	*ptr = p;
	return (t);
}

/**
 * sigintHandler - block ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
