#include "pat.h"

/**
 * delete_data - initializes data_t struct
 * @info: struct address
 */
void delete_data(data_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->locat = NULL;
	info->argc = 0;
}

/**
 * set_data - initializes data_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_data(data_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strwords(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strduplicates(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		swap_alias(info);
		swap_var(info);
	}
}

/**
 * free_data - frees data_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_data(data_t *info, int all)
{
	fstr(info->argv);
	info->argv = NULL;
	info->locat = NULL;
	if (all)
	{
		if (!info->command_buf)
			free(info->arg);
		if (info->env)
			free_write(&(info->env));
		if (info->history)
			free_write(&(info->history));
		if (info->alias)
			free_write(&(info->alias));
		fstr(info->environ);
			info->environ = NULL;
		pfree((void **)info->command_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putcharacter(BUF_FLUSH);
	}
}
