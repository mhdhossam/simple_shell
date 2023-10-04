#include "pat.h"

/**
 *_einputs - prints an input string
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void _einputs(char *string)
{
	int i = 0;

	if (!string)
		return;
	while (string[i] != '\0')
	{
		_eputcharacter(string[i]);
		i++;
	}
}

/**
 * _eputcharacter - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputcharacter(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _inputfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _inputfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_inputsfd - prints an input string
 * @string: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _inputsfd(char *string, int fd)
{
	int i = 0;

	if (!string)
		return (0);
	while (*string)
	{
		i += _inputfd(*string++, fd);
	}
	return (i);
}
