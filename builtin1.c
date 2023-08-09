#include "shell.h"

/**
 * _myhistory - displays history list, one command by line, followed
 *              by line numbers, starting 0.
 * @info: Structure containing arguments. maintain
 *        constant function prototype.
 *  Return: 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - set alias to string
 * @info: the parameter struct
 * @str: string alias
 *
 * Return: 0 (success), 1 (error)
 */
int unset_alias(info_t *info, char *str)
{
	char *q, d;
	int r;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	d = *q;
	*q = 0;
	r = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*q = d;
	return (r);
}

/**
 * set_alias - sets alias to string
 * @info: the parameter struct
 * @str: string alias
 *
 * Return: 0(success), 1(error)
 */
int set_alias(info_t *info, char *str)
{
	char *q;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: alias node
 *
 * Return: 0 (success), 1 (error)
 */
int print_alias(list_t *node)
{
	char *q = NULL, *b = NULL;

	if (node)
	{
		q = _strchr(node->str, '=');
		for (b = node->str; b <= q; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimic alias builtin (man alias)
 * @info: Structure containing arguments. Used maintain
 *          constant function prototype.
 *  Return: 0
 */
int _myalias(info_t *info)
{
	int j = 0;
	char *q = NULL;
	list_t *nde = NULL;

	if (info->argc == 1)
	{
		nde = info->alias;
		while (nde)
		{
			print_alias(nde);
			nde = nde->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		q = _strchr(info->argv[j], '=');
		if (q)
			set_alias(info, info->argv[j]);
		else
			print_alias(node_starts_with(info->alias, info->argv[j], '='));
	}

	return (0);
}
