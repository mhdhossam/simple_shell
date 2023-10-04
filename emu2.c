#include "pat.h"

/**
 * create_alias - sets alias to a string
 * @info: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int create_alias(data_t *info, char *string)
{
	char *i;

	i = _strcharacter(string, '=');
	if (!i)
		return (1);
	if (!*++i)
		return (de_alias(info, string));

	de_alias(info, string);
	return (add_node_end(&(info->alias), string, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(write_t *node)
{
	char *i = NULL, *p = NULL;

	if (node)
	{
		i = _strcharacter(node->string, '=');
		for (p = node->string; p <= i; p++)
			_putcharacter(*p);
		_putcharacter('\'');
		_input(i + 1);
		_input("'\n");
		return (0);
	}
	return (1);
}

/**
 * _this_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          a constant function prototype.
 *
 * Return: Always 0
 */
int _this_alias(data_t *info)
{
	int m = 0;
	char *k = NULL;
	write_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (m = 1; info->argv[m]; m++)
	{
		k = _strcharacter(info->argv[m], '=');
		if (k)
		{
			create_alias(info, info->argv[m]);
		}
		else
		{
			print_alias(node_begin_with(info->alias, info->argv[m], '='));
		}
	}

	return (0);
}

