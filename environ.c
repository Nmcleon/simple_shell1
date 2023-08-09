#include "shell.h"

/**
 * _myenv - prints current environment
 * @info: Structure containing arguments. maintains
 *          constant function prototype.
 * Return: 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - get value of environ variable
 * @info: Structure containing arguments. maintains
 * @name: env var name
 *
 * Return: value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *nde = info->env;
	char *q;

	while (nde)
	{
		q = starts_with(nde->str, name);
		if (q && *q)
			return (q);
		nde = nde->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize new environment variable,
 *             /modify an existing one
 * @info: Structure containing arguments. maintain
 *        constant function prototype.
 *  Return: 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove environment variable
 * @info: Structure containing arguments. maintain
 *        constant function prototype.
 *  Return: 0
 */
int _myunsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		_unsetenv(info, info->argv[j]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing arguments. maintain
 *          constant function prototype.
 * Return: 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&node, environ[j], 0);
	info->env = node;
	return (0);
}
