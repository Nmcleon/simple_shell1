#include "shell.h"

/**
 * main - entry point into program
 *
 * @ac: args count
 * @av: array of args
 *
 * Return: 0 for success
 * else, 1 for error
 */

int main(int ac, char **av)
{
	info_t inform[] = {INFO_INIT};
	int f = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(f)
		: "r"(f));

	if (ac == 2)
	{
		f = open(av[1], O_RDONLY);
		if (f == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inform->readfd = f;
	}
	populate_env_list(inform);
	read_history(inform);
	hsh(inform, av);
	return (EXIT_SUCCESS);
}
