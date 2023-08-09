#include "shell.h"

/**
 * _strlen - returns len of a string
 *
 * @s: string to check
 *
 * Return: int len of string
 */

int _strlen(char *s)
{
	int a = 0;

	if (!s)
		return (0);

	while (*s++)
		a++;
	return (a);
}

/**
 * _strcmp - does lexicogarphic comparison of two strangs
 *
 * @s1: 1st strang
 * @s2: 2nd strang
 *
 * Return: -ve, if s1 < s2
 * +ve, if s1 > s2
 * 0, if s1 == s2
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with the  haystack
 *
 * @haystack: string val to search
 * @needle: substr to find
 *
 * Return: addr of next char of haystack/NULL
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 *
 * @dest: destination buffer
 * @src: initial buffer
 *
 * Return: pointer to destination buffer
 */

char *_strcat(char *dest, char *src)
{
	char *rt = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (rt);
}
