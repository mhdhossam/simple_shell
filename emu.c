#include "pat.h"

/**
 * _terminate - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit state
 *         (0) if info.argv[0] != "exit"
 */
int _terminate(data_t *info)
{
	int tercheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		tercheck = _conv_string(info->argv[1]);
		if (tercheck == -1)
		{
			info->status = 2;
			print_err(info, "Illegal number: ");
			_einputs(info->argv[1]);
			_eputcharacter('\n');
			return (1);
		}
		info->error_number = _conv_string(info->argv[1]);
		return (-2);
	}
	info->error_number = -1;
	return (-2);
}

/**
 * _currdest - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _currdest(data_t *info)
{
	char *x, *directo, buff[1024];
	int currdirec_return;

	x = getcwd(buff, 1024);
	if (!x)
		_input("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		directo = _getenviroment(info, "HOME=");
		if (!directo)
			currdirec_return = chdir(
			(directo = _getenviroment(info, "PWD=")) ? directo : "/");
		else
			currdirec_return = chdir(directo);
	}
	else if (_stringcomparison(info->argv[1], "-") == 0)
	{
		if (!_getenviroment(info, "OLDPWD="))
		{
			_input(x);
			_putcharacter('\n');
			return (1);
		}
		_input(_getenviroment(info, "OLDPWD=")), _putcharacter('\n');
		currdirec_return = chdir(
		(directo = _getenviroment(info, "OLDPWD=")) ? directo : "/");
	}
	else
		currdirec_return = chdir(info->argv[1]);
	if (currdirec_return == -1)
	{
		print_err(info, "can't cd to ");
		_einputs(info->argv[1]), _eputcharacter('\n');
	}
	else
	{
		_setenviroment(info, "OLDPWD", _getenviroment(info, "PWD="));
		_setenviroment(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _helpme - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _helpme(data_t *info)
{
	char **args_arrays;

	args_arrays = info->argv;
	_input("help call works. Function not yet implemented \n");
	if (0)
		_input(*args_arrays); /* temp att_unused workaround */
	return (0);
}

/**
 * _this_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _this_history(data_t *info)
{
	print_write(info->history);
	return (0);
}


/**
 * de_alias - sets alias to string
 * @info: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */

int de_alias(data_t *info, char *string)
{
	char *i, l;
	int result;

	i = _strcharacter(string, '=');
	if (!i)
		return (1);
	l = *i;
	*i = 0;
	result = clear_node_at_index(&(info->alias),
		gets_node_index(info->alias, node_begin_with(info->alias, string, -1)));
	*i = l;
	return (result);
}


