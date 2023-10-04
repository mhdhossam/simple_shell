#include "pat.h"

/**
 * is_chainz - test if current char in buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_chainz(data_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->command_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->command_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->command_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chainz - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chainz(data_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->command_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->command_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * swap_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int swap_alias(data_t *info)
{
	int i;
	write_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_begin_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strcharacter(node->string, '=');
		if (!p)
			return (0);
		p = _strduplicates(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * swap_var - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int swap_var(data_t *info)
{
	int i = 0;
	write_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_stringcomparison(info->argv[i], "$?"))
		{
			swap_str(&(info->argv[i]),
				_strduplicates(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_stringcomparison(info->argv[i], "$$"))
		{
			swap_str(&(info->argv[i]),
				_strduplicates(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_begin_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			swap_str(&(info->argv[i]),
				_strduplicates(_strcharacter(node->string, '=') + 1));
			continue;
		}
		swap_str(&info->argv[i], _strduplicates(""));

	}
	return (0);
}

/**
 * swap_str - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int swap_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
