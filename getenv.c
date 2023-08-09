#include "shell.h"

/**
 * get_environ - returns the string array copy of environ
 * @info: Structure containing arguments. maintains
 *          constant function prototype.
 * Return: 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove environment variable
 * @info: Structure containing srguments. Maintain
 *        constant function prototype.
 *  Return: 1 (delete), else 0
 * @var: string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	char *q;
	size_t j = 0;

	if (!node || !var)
		return (0);

	while (node)
	{
		q = starts_with(node->str, var);
		if (q && *q == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), j);
			j = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		j++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize new environment variable,
 *             /modify an existing one
 * @info: Structure containing arguments.maintain
 *        constant function prototype.
 * @var: string env var property
 * @value: string env var value
 *  Return: 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	char *q;
	list_t *node;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		q = starts_with(node->str, var);
		if (q && *q == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
