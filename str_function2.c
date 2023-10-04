#include "pat.h"

/**
 * _strduplicates - duplicates a string
 * @string: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strduplicates(const char *string)
{
	int l = 0;
	char *ret;

	if (string == NULL)
		return (NULL);
	while (*string++)
		l++;
	ret = malloc(sizeof(char) * (l + 1));
	if (!ret)
		return (NULL);
	for (l++; l--;)
		ret[l] = *--string;
	return (ret);
}

/**
 *_input - prints an input string
 *@string: the string to be printed
 *
 * Return: Nothing
 */
void _input(char *string)
{
	int m = 0;

	if (!string)
		return;
	while (string[m] != '\0')
	{
		_putcharacter(string[m]);
		m++;
	}
}

/**
 * _putcharacter - writes the character c to stdout
 * @p: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putcharacter(char p)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (p == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (p != BUF_FLUSH)
		buf[i++] = p;
	return (1);
}

/**
 **_strncopies - copies a string
 *@index: the index string to be copied to
 *@source: the source string
 *@t: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncopies(char *index, char *source, int t)
{
	int i, j;
	char *m = index;

	i = 0;
	while (source[i] != '\0' && i < t - 1)
	{
		index[i] = source[i];
		i++;
	}
	if (i < t)
	{
		j = i;
		while (j < t)
		{
			index[j] = '\0';
			j++;
		}
	}
	return (m);
}

/**
 **_strncon - concatenates two strings
 *@index: the first string
 *@source: the second string
 *@t: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncon(char *index, char *source, int t)
{
	int i, j;
	char *m = index;

	i = 0;
	j = 0;
	while (index[i] != '\0')
		i++;
	while (source[j] != '\0' && j < t)
	{
		index[i] = source[j];
		i++;
		j++;
	}
	if (j < t)
		index[i] = '\0';
	return (m);
}
