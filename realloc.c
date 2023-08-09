#include "shell.h"

/**
 * _memset - fills mem with a const byte
 *
 * @s: pointer to mem area
 * @b: byte to fill *s with
 * @n: amnt of bytes to be filled
 *
 * Return: pointer to mem area s
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		s[a] = b;
	return (s);
}

/**
 * ffree - frees  string of strings
 *
 * @pp: string of strings
 */

void ffree(char **pp)
{
	char **fr = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(fr);
}

/**
 * _realloc - reallocates some block of memory
 *
 * @ptr: pointer to previous malloc block
 * @old_size: byte size of last block
 * @new_size: byte size of new block
 *
 * Return: pointer to old block
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *j;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	j = malloc(new_size);
	if (!j)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		j[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (j);
}
