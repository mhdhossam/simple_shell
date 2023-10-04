#include "pat.h"

/**
 * get_environment - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environment(data_t *info)
{
	if (!info->environ || info->enviroment_changed)
	{
		info->environ = write_to_strings(info->env);
		info->enviroment_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenviroment - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenviroment(data_t *info, char *var)
{
	write_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = begin_with(node->string, var);
		if (p && *p == '=')
		{
			info->enviroment_changed = clear_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->enviroment_changed);
}

/**
 * _setenviroment - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenviroment(data_t *info, char *var, char *value)
{
	char *buf = NULL;
	write_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_stringlength(var) + _stringlength(value) + 2);
	if (!buf)
		return (1);
	_stringcopies(buf, var);
	_strcon(buf, "=");
	_strcon(buf, value);
	node = info->env;
	while (node)
	{
		p = begin_with(node->string, var);
		if (p && *p == '=')
		{
			free(node->string);
			node->string = buf;
			info->enviroment_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->enviroment_changed = 1;
	return (0);
}
