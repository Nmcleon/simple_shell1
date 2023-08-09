#include "shell.h"

/**
 * list_len - determines length of linked list
 *
 * @h: pointer to 1st node
 *
 * Return: list size
 */

size_t list_len(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * list_to_strings - returns array of strings of the list->str
 *
 * @head: pointer to 1st node
 *
 * Return: array of strings
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t a = list_len(head), b;
	char **strs;
	char *str;

	if (!head || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (b = 0; b < a; b++)
				free(strs[b]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}

/**
 * print_list - prints all elements of a list_t list
 *
 * @h: pointer to 1st node
 *
 * Return: list size
 */

size_t print_list(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 *
 * @node: pointer to list head
 * @prefix: string to match
 * @c: next x-ter after prefix to match
 *
 * Return: match node
 * else, null
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *r = NULL;

	while (node)
	{
		r = starts_with(node->str, prefix);
		if (r && ((c == -1) || (*r == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets index of a node
 *
 * @head: pointer  head node
 * @node: pointer to the node
 *
 * Return: index of node
 * else, -1
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t x = 0;

	while (head)
	{
		if (head == node)
			return (x);
		head = head->next;
		x++;
	}
	return (-1);
}
