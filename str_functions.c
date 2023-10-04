#include "pat.h"

/**
 * _stringlength- returns the length of a string
 * @p: the string whose length to check
 *
 * Return: integer length of string
 */
int _stringlength(char *p)
{
	int m = 0;

	if (!p)
		return (0);

	while (*p++)
		m++;
	return (m);
}

/**
 * _stringcomparison - performs lexicogarphic comparison of two strangs.
 * @m1: the first strang
 * @m2: the second strang
 *
 * Return: negative if m1 < m2, positive if m1 > m2, zero if m1 == m2
 */
int _stringcomparison(char *m1, char *m2)
{
	while (*m1 && *m2)
	{
		if (*m1 != *m2)
			return (*m1 - *m2);
		m1++;
		m2++;
	}
	if (*m1 == *m2)
		return (0);
	else
		return (*m1 < *m2 ? -1 : 1);
}

/**
 * begin_with - checks if needle starts with hs
 * @hs: string to search
 * @ne: the substring to find
 *
 * Return: address of next char of hs or NULL
 */
char *begin_with(const char *hs, const char *ne)
{
	while (*ne)
		if (*ne++ != *hs++)
			return (NULL);
	return ((char *)hs);
}

/**
 * _strcon - concatenates two strings
 * @index: the destination buffer
 * @source_buffer: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcon(char *index, char *source_buffer)
{
	char *result = index;

	while (*index)
		index++;
	while (*source_buffer)
		*index++ = *source_buffer++;
	*index = *source_buffer;
	return (result);
}

/**
 * _stringcopies - copies a string
 * @index: the index
 * @src: the source
 *
 * Return: pointer to index
 */
char *_stringcopies(char *index, char *src)
{
	int m = 0;

	if (index == src || src == 0)
		return (index);
	while (src[m])
	{
		index[m] = src[m];
		m++;
	}
	index[m] = 0;
	return (index);
}

