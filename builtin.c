#include "shell.h"

/**
 * _myexit - exit shell
 * @info: Structure containing arguments. Maintain
 *          constant function prototype.
 *  Return: exits with exit status
 */
int _myexit(info_t *info)
{
	int exitchk;

	if (info->argv[1])
	{
		exitchk = _erratoi(info->argv[1]);
		if (exitchk == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes current directory of the process
 * @info: Structure containing arguments. maintain
 *          constant function prototype.
 *  Return: 0
 */
int _mycd(info_t *info)
{
	char *d, *di, buffer[1024];
	int chdir_ret;

	d = getcwd(buffer, 1024);
	if (!d)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		di = _getenv(info, "HOME=");
		if (!di)
			chdir_ret =
				chdir((di = _getenv(info, "PWD=")) ? di : "/");
		else
			chdir_ret = chdir(di);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(d);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((di = _getenv(info, "OLDPWD=")) ? di : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the directory of the process
 * @info: Structure containing arguments. maintain
 *          constant function prototype.
 *  Return: 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
