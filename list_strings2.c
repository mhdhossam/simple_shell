#include "pat.h"

/**
 * write_len - determines length of linked list
 * @f: pointer to first node
 *
 * Return: size of list
 */
size_t write_len(const write_t *f)
{
	size_t i = 0;

	while (f)
	{
		f = f->next;
		i++;
	}
	return (i);
}

/**
 * write_to_strings - returns an array of strings of the write->string
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **write_to_strings(write_t *head)
{
	write_t *node = head;
	size_t i = write_len(head), j;
	char **strs;
	char *string;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		string = malloc(_stringlength(node->string) + 1);
		if (!string)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		string = _stringcopies(string, node->string);
		strs[i] = string;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_write - prints all elements of a write_t linked list
 * @m: pointer to first node
 *
 * Return: size of list
 */
size_t print_write(const write_t *m)
{
	size_t i = 0;

	while (m)
	{
		_input(convert_number(m->number, 10, 0));
		_putcharacter(':');
		_putcharacter(' ');
		_input(m->string ? m->string : "(nil)");
		_input("\n");
		m = m->next;
		i++;
	}
	return (i);
}

/**
 * node_begin_with - returns node whose string begin with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
write_t *node_begin_with(write_t *node, char *prefix, char c)
{
	char *p  = NULL;

	while (node)
	{
		p = begin_with(node->string, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * gets_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t gets_node_index(write_t *head, write_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
