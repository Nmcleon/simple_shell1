#include "shell.h"

/**
 * bfree - frees some pointer and NULLs the addr
 *
 * @ptr: pointer address
 *
 * Return: 1, if free
 * else, 0
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
