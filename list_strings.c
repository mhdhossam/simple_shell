#include "pat.h"

/**
 * add_node_start - adds a node to the start of the write
 * @head: address of pointer to head node
 * @string: str field of node
 * @number: node index used by history
 *
 * Return: size of write
 */
write_t *add_node_start(write_t **head, const char *string, int number)
{
	write_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(write_t));
	if (!new_head)
		return (NULL);
	_memorycon((void *)new_head, 0, sizeof(write_t));
	new_head->number = number;
	if (string)
	{
		new_head->string = _strduplicates(string);
		if (!new_head->string)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the write
 * @head: address of pointer to head node
 * @string: str field of node
 * @number: node index used by history
 *
 * Return: size of write
 */
write_t *add_node_end(write_t **head, const char *string, int number)
{
	write_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(write_t));
	if (!new_node)
		return (NULL);
	_memorycon((void *)new_node, 0, sizeof(write_t));
	new_node->number = number;
	if (string)
	{
		new_node->string = _strduplicates(string);
		if (!new_node->string)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_write_string - prints only the string element of a write_t linked list
 * @m: pointer to first node
 *
 * Return: size of list
 */
size_t print_write_string(const write_t *m)
{
	size_t i = 0;

	while (m)
	{
		_input(m->string ? m->string : "(nil)");
		_input("\n");
		m = m->next;
		i++;
	}
	return (i);
}

/**
 * clear_node_at_index - clears node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int clear_node_at_index(write_t **head, unsigned int index)
{
	write_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->string);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->string);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_write - frees all nodes of a list
 * @head_pointer: address of pointer to head node
 *
 * Return: void
 */
void free_write(write_t **head_pointer)
{
	write_t *node, *next_node, *head;

	if (!head_pointer || !*head_pointer)
		return;
	head = *head_pointer;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->string);
		free(node);
		node = next_node;
	}
	*head_pointer = NULL;
}


