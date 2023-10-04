#include "pat.h"

/**
 **_strcharacter  - locates a character in a string
 *@p: the string to be parsed
 *@s: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strcharacter(char *p, char s)
{
	do {
		if (*p == s)
			return (p);
	} while (*p++ != '\0');

	return (NULL);
}

/**
 * **strwords - splits a string into words. Repeat delimiters are ignored
 * @string: the input string
 * @p: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strwords(char *string, char *p)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!p)
		p = " ";
	for (i = 0; string[i] != '\0'; i++)
		if (!delim_char(string[i], p) && (delim_char(string[i + 1], p) ||
		!string[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (delim_char(string[i], p))
			i++;
		k = 0;
		while (!delim_char(string[i + k], p) && string[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = string[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strwords2 - splits a string into words
 * @string: the input string
 * @p: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strwords2(char *string, char p)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (i = 0; string[i] != '\0'; i++)
		if ((string[i] != p && string[i + 1] == p) ||
		    (string[i] != p && !string[i + 1]) || string[i + 1] == p)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (string[i] == p && string[i] != p)
			i++;
		k = 0;
		while (string[i + k] != p && string[i + k] && string[i + k] != p)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = string[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}



