#include "shell.h"

/**
 * is_chain - tests if current char in buffer is a chain delimeter
 *
 * @info: param struct
 * @buf: char buffer
 * @p: addr of current position in buffer
 *
 * Return: 1, if chain delimeter
 * else, 0
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t b = *p;

	if (buf[b] == '|' && buf[b + 1] == '|')
	{
		buf[b] = 0;
		b++;
		info->cmd_buf_type = CMD_OR;
	} else if (buf[b] == '&' && buf[b + 1] == '&')
	{
		buf[b] = 0;
		b++;
		info->cmd_buf_type = CMD_AND;
	} else if (buf[b] == ';')
	{
		buf[b] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	} else
		return (0);
	*p = b;
	return (1);
}

/**
 * check_chain - checks if we should continue chaining
 * based on the last status
 *
 * @info: param struct
 * @buf: char buffer
 * @p: addr of current position in buffer
 * @i: starting position in buffer
 * @len: len of buffer
 *
 * Return: Nothing
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t b = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			b = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			b = len;
		}
	}
	*p = b;
}

/**
 * replace_alias - replaces aliases in the tokenized string
 *
 * @info: param struct
 *
 * Return: 1, if replaced
 * else, 0
 */

int replace_alias(info_t *info)
{
	int a;
	list_t *nd;
	char *p;

	for (a = 0; a < 10; a++)
	{
		nd = node_starts_with(info->alias, info->argv[0], '=');
		if (!nd)
			return (0);
		free(info->argv[0]);
		p = _strchr(nd->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in tokenized string
 *
 * @info: param struct
 *
 * Return: 1, if replaced
 * else, 0
 */

int replace_vars(info_t *info)
{
	int a = 0;
	list_t *nd;

	for (a = 0; info->argv[a]; a++)
	{
		if (info->argv[a][0] != '$' || !info->argv[a][1])
			continue;

		if (!_strcmp(info->argv[a], "$?"))
		{
			replace_string(&(info->argv[a]),
						   _strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[a], "$$"))
		{
			replace_string(&(info->argv[a]),
						   _strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nd = node_starts_with(info->env, &info->argv[a][1], '=');
		if (nd)
		{
			replace_string(&(info->argv[a]),
						   _strdup(_strchr(nd->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[a], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - replaces the string
 *
 * @old: addr of old string
 * @new: new string
 *
 * Return: 1, if replaced
 * else, 0
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
