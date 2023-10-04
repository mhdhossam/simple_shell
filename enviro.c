#include "pat.h"

/**
 * _myenviroment - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenviroment(data_t *info)
{
	print_write_string(info->env);
	return (0);
}

/**
 * _getenviroment - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenviroment(data_t *info, const char *name)
{
	write_t *node = info->env;
	char *p;

	while (node)
	{
		p = begin_with(node->string, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenviroment - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenviroment(data_t *info)
{
	if (info->argc != 3)
	{
		_einputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenviroment(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenviroment - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenviroment(data_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_einputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenviroment(info, info->argv[i]);

	return (0);
}

/**
 * populate_enviroment_write - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_enviroment_write(data_t *info)
{
	write_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
