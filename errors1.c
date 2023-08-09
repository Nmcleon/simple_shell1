#include "shell.h"

/**
 * _erratoi - converts string to an integer
 * @s: string to be converted
 * Return: 0 no numbers in string,else
 *       -1 on error
 */
int _erratoi(char *s)
{
	int j = 0;
	unsigned long int r = 0;

	if (*s == '+')
		s++;
	for (j = 0;  s[j] != '\0'; j++)
	{
		if (s[j] >= '0' && s[j] <= '9')
		{
			r *= 10;
			r += (s[j] - '0');
			if (r > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (r);
}

/**
 * print_error - prints error message
 * @info: parameter & return info struct
 * @estr: string containing error
 * Return: 0 no numbers in string, otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function print decimal (integer) number (base 10)
 * @input: input
 * @fd: filedescriptor to write to
 *
 * Return: number of character printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, c = 0;
	unsigned int _abs_, new;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		c++;
	}
	else
		_abs_ = input;
	new = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + new / j);
			c++;
		}
		new %= j;
	}
	__putchar('0' + new);
	c++;

	return (c);
}

/**
 * convert_number - converter function
 * @num: number
 * @base: the base
 * @flags: argument flags
 *
 * Return: a string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char s = 0;
	char *p;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		s = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buffer[49];
	*p = '\0';

	do	{
		*--p = array[n % base];
		n /= base;
	} while (n != 0);

	if (s)
		*--p = s;
	return (p);
}

/**
 * remove_comments - function replace first instance of '#' with '\0'
 * @buf: address of string to modify
 *
 * Return: 0;
 */
void remove_comments(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
}
