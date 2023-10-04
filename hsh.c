#include "pat.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(data_t *info, char **av)
{
	ssize_t r = 0;
	int buildin_result = 0;

	while (r != -1 && buildin_result != -2)
	{
		delete_data(info);
		if (active_mode(info))
			_input("$ ");
		_eputcharacter(BUF_FLUSH);
		r = gets_input(info);
		if (r != -1)
		{
			set_data(info, av);
			buildin_result = find_buildin(info);
			if (buildin_result == -1)
				find_command(info);
		}
		else if (active_mode(info))
			_putcharacter('\n');
		free_data(info, 0);
	}
	write_historys(info);
	free_data(info, 1);
	if (!active_mode(info) && info->status)
		exit(info->status);
	if (buildin_result == -2)
	{
		if (info->error_number == -1)
			exit(info->status);
		exit(info->error_number);
	}
	return (buildin_result);
}

/**
 * find_buildin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_buildin(data_t *info)
{
	int i, build_in_result = -1;
	buildin_tables buildintbls[] = {
		{"exit", _terminate},
		{"env", _myenviroment},
		{"help", _helpme},
		{"history", _this_history},
		{"setenv", _mysetenviroment},
		{"unsetenv", _myunsetenviroment},
		{"cd", _currdest},
		{"alias", _this_alias},
		{NULL, NULL}
	};

	for (i = 0; buildintbls[i].type; i++)
		if (_stringcomparison(info->argv[0], buildintbls[i].type) == 0)
		{
			info->l_count++;
			build_in_result = buildintbls[i].func(info);
			break;
		}
	return (build_in_result);
}

/**
 * find_command - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_command(data_t *info)
{
	char *locat = NULL;
	int i, k;

	info->locat = info->argv[0];
	if (info->lcount_flag == 1)
	{
		info->l_count++;
		info->lcount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!delim_char(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	locat = find_cmd_locat(info, _getenviroment(info, "PATH="), info->argv[0]);
	if (locat)
	{
		info->locat = locat;
		fork_command(info);
	}
	else
	{
		if ((active_mode(info) || _getenviroment(info, "PATH=")
			|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_err(info, "not found\n");
		}
	}
}

/**
 * fork_command - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_command(data_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->locat, info->argv, get_environment(info)) == -1)
		{
			free_data(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_err(info, "Permission denied\n");
		}
	}
}
