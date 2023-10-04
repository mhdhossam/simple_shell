#include "pat.h"

/**
 * input_buffers - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @length: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buffers(data_t *info, char **buf, size_t *length)
{
	ssize_t r = 0;
	size_t length_p = 0;

	if (!*length)
	{
		/* pfree((void **)info->command_buf); */
		free(*buf);
		*buf = NULL;
		signal(SIGINT, blocksHandler);
#if USE_GETLINE
		r = findline(buf, &length_p, stdin);
#else
		r = _findline(info, buf, &length_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->lcount_flag = 1;
			remove_comms(*buf);
			build_history_write(info, *buf, info->histcount++);
			/* if (_strcharacter(*buf, ';')) is this a command chain? */
			{
				*length = r;
				info->command_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * gets_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t gets_input(data_t *info)
{
	static char *buf;
	static size_t i, j, length;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putcharacter(BUF_FLUSH);
	r = input_buffers(info, &buf, &length);
	if (r == -1)
		return (-1);
	if (length)
	{
		j = i;
		p = buf + i;

		check_chainz(info, buf, &j, i, length);
		while (j < length)
		{
			if (is_chainz(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= length)
		{
			i = length = 0;
			info->command_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_stringlength(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buffers - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buffers(data_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _findline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _findline(data_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, leng;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == leng)
		i = leng = 0;

	r = read_buffers(info, buf, &leng);
	if (r == -1 || (r == 0 && leng == 0))
		return (-1);

	c = _strcharacter(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : leng;
	new_p = _reallocates(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncon(new_p, buf + i, k - i);
	else
		_strncopies(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * blocksHandler - blocks ctrl-C
 * @sig_number: the signal number
 *
 * Return: void
 */
void blocksHandler(__attribute__((unused)) int sig_number)
{
	_input("\n");
	_input("$ ");
	_putcharacter(BUF_FLUSH);
}

