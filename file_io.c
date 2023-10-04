#include "pat.h"

/**
 * gets_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */

char *gets_history_file(data_t *info)
{
	char *buf, *directo, _stringlen;

	directo = _getenviroment(info, "HOME=");
	if (!directo)
		return (NULL);
	_stringlen = (_stringlength(directo) + _stringlength(HIST_FILE) + 2);
	buf = malloc(sizeof(char) * _stringlen);
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_stringcopies(buf, directo);
	_stringcopies(buf, "/");
	_stringcopies(buf, HIST_FILE);
	return (buf);
}

/**
 * write_historys - creates a file or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_historys(data_t *info)
{
	ssize_t fd;
	char *filename = gets_history_file(info);
	write_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_inputsfd(node->string, fd);
		_inputfd('\n', fd);
	}
	_inputfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * reads_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int reads_history(data_t *info)
{
	int i, last = 0, lcount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = gets_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_write(info, buf + last, lcount++);
			last = i + 1;
		}
	if (last != i)
		build_history_write(info, buf + last, lcount++);
	free(buf);
	info->histcount = lcount;
	while (info->histcount-- >= HIST_MAX)
		clear_node_at_index(&(info->history), 0);
	renum_history(info);
	return (info->histcount);
}

/**
 * build_history_write - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @lcount: the history line count, histcount
 *
 * Return: Always 0
 */
int build_history_write(data_t *info, char *buf, int lcount)
{
	write_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, lcount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renum_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renum_history(data_t *info)
{
	write_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->number = i++;
		node = node->next;
	}
	return (info->histcount = i);
}

