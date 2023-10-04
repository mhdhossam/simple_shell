#include "pat.h"

/**
 * active_mode - returns true if shell is interactive mode
 * @data: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int active_mode(data_t *data)
{
	return (isatty(STDIN_FILENO) && data->readfd <= 2);
}

/**
 * delim_char - checks if character is a delimiter
 * @m: the char to check
 * @delim: the delimiter string
 * Return: 1 if true, 0 if false
 */
int delim_char(char m, char *delim)
{
	while (*delim)
		if (*delim++ == m)
			return (1);
	return (0);
}

/**
 *_isalpha_char - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */
int _isalpha_char(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_str_conv - converts a string to an integer
 *@c: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */
int _str_conv(char *c)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; c[i] != '\0' && flag != 2; i++)
	{
		if (c[i] == '-')
			sign *= -1;

		if (c[i] >= '0' && c[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (c[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 * _conv_string - converts a string to an integer
 * @sc: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _conv_string(char *sc)
{
	int i = 0;
	unsigned long int results = 0;

	if (*sc == '+')
		sc++;
	for (i = 0; sc[i] != '\0'; i++)
	{
		if (sc[i] >= '0' && sc[i] <= '9')
		{
			results *= 10;
			results += (sc[i] - '0');
			if (results > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (results);
}

