#include "pat.h"

/**
 * is_command - determines if a file is an executable command
 * @info: the info struct
 * @locat: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_command(data_t *info, char *locat)
{
	struct stat pt;

	(void)info;
	if (!locat || stat(locat, &pt))
		return (0);

	if (pt.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicates_chars - duplicates characters
 * @locatstring: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicates_chars(char *locatstring, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (locatstring[i] != ':')
			buf[k++] = locatstring[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_cmd_locat - finds this cmd in the PATH string
 * @info: the info struct
 * @locatstring: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_cmd_locat(data_t *info, char *locatstring, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *locat;

	if (!locatstring)
		return (NULL);
	if ((_stringlength(cmd) > 2) && begin_with(cmd, "./"))
	{
		if (is_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!locatstring[i] || locatstring[i] == ':')
		{
			locat = duplicates_chars(locatstring, curr_pos, i);
			if (!*locat)
				_strcon(locat, cmd);
			else
			{
				_strcon(locat, "/");
				_strcon(locat, cmd);
			}
			if (is_command(info, locat))
				return (locat);
			if (!locatstring[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
