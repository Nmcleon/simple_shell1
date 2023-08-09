#include "shell.h"

/**
 * add_node - adds node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: the size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *n_head;

	if (!head)
		return (NULL);
	n_head = malloc(sizeof(list_t));
	if (!n_head)
		return (NULL);
	_memset((void *)n_head, 0, sizeof(list_t));
	n_head->num = num;
	if (str)
	{
		n_head->str = _strdup(str);
		if (!n_head->str)
		{
			free(n_head);
			return (NULL);
		}
	}
	n_head->next = *head;
	*head = n_head;
	return (n_head);
}

/**
 * add_node_end - add a node to the end of the list
 * @head: address of pointer to head node
 * @str: the str field of node
 * @num: a node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *n_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	n_node = malloc(sizeof(list_t));
	if (!n_node)
		return (NULL);
	_memset((void *)n_node, 0, sizeof(list_t));
	n_node->num = num;
	if (str)
	{
		n_node->str = _strdup(str);
		if (!n_node->str)
		{
			free(n_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = n_node;
	}
	else
		*head = n_node;
	return (n_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: the pointer to first node
 *
 * Return: the size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: an address of pointer to first node
 * @index: the index of node to delete
 *
 * Return: 1 (success), 0 (failure)
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *p_node;
	unsigned int j = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (j == index)
		{
			p_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		j++;
		p_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - free all nodes of list
 * @head_ptr: the address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *nxt_node, *h;

	if (!head_ptr || !*head_ptr)
		return;
	h = *head_ptr;
	node = h;
	while (node)
	{
		nxt_node = node->next;
		free(node->str);
		free(node);
		node = nxt_node;
	}
	*head_ptr = NULL;
}
