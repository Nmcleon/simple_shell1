#include "shell.h"

/**
 **_strncpy - copies of string
 *@dest: destination string to be copied
 *@src: source string
 *@n: amount of characters to be copied
 *Return: concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int j, k;
	char *sl = dest;

	j = 0;
	while (src[j] != '\0' && j < n - 1)
	{
		dest[j] = src[j];
		j++;
	}
	if (j < n)
	{
		k = j;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (sl);
}

/**
 **_strncat - concatenate two strings
 *@dest: first string
 *@src: second string
 *@n: amount of bytes to be maximally used
 *Return: concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int j, k;
	char *s = dest;

	j = 0;
	k = 0;
	while (dest[j] != '\0')
		j++;
	while (src[k] != '\0' && k < n)
	{
		dest[j] = src[k];
		j++;
		j++;
	}
	if (k < n)
		dest[j] = '\0';
	return (s);
}

/**
 **_strchr - locates character in string
 *@s: string to be parsed
 *@c: character to look for
 *Return: (s) pointer to memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
		{
			return (s);
		}
	} while (*s++ != '\0');

	return (NULL);
}
