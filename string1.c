#include "shell.h"

/**
 * _strcpy - makes copies of a string
 *
 * @dest: destination
 * @src: source
 *
 * Return: pointer to destination
 */

char *_strcpy(char *dest, char *src)
{
	int a = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = 0;
	return (dest);
}

/**
 * _strdup - makes duplicates of a string
 *
 * @str: string to duplicate
 *
 * Return: pointer to the duplicated string
 */

char *_strdup(const char *str)
{
	int len = 0;
	char *rt;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	rt = malloc(sizeof(char) * (len + 1));
	if (!rt)
		return (NULL);
	for (len++; len--;)
		rt[len] = *--str;
	return (rt);
}

/**
 * _puts - prints some input string
 *
 * @str: string to be printed
 *
 * Return: Nothing
 */

void _puts(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_putchar(str[a]);
		a++;
	}
}

/**
 * _putchar - writes the x-ter c to stdout
 *
 * @c: x-ter to print
 *
 * Return: 1, for success
 * -1, for error & errno is set
 */

int _putchar(char c)
{
	static int a;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buff, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buff[a++] = c;
	return (1);
}
