#include "pat.h"

/**
 * print_err - prints an error message
 * @info: the parameter & return info struct
 * @errstr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_err(data_t *info, char *errstr)
{
	_einputs(info->fname);
	_einputs(": ");
	print_dec(info->l_count, STDERR_FILENO);
	_einputs(": ");
	_einputs(info->argv[0]);
	_einputs(": ");
	_einputs(errstr);
}

/**
 * print_dec - function prints a decimal (integer) number (base 10)
 * @ipu: the input
 * @fpd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_dec(int ipu, int fpd)
{
	int (*__putcharacter)(char) = _putcharacter;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fpd == STDERR_FILENO)
		__putcharacter = _eputcharacter;
	if (ipu < 0)
	{
		_abs_ = -ipu;
		__putcharacter('-');
		count++;
	}
	else
		_abs_ = ipu;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putcharacter('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putcharacter('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @number: number
 * @bases: base
 * @flag: argument flags
 *
 * Return: string
 */
char *convert_number(long int number, int bases, int flag)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = number;

	if (!(flag & CONVERT_UNSIGNED) && number < 0)
	{
		n = -number;
		sign = '-';
	}
	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % bases];
		n /= bases;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comms - function replaces the first instance of '#' with '\0'
 * @add_buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comms(char *add_buf)
{
	int i;

	for (i = 0; add_buf[i] != '\0'; i++)
		if (add_buf[i] == '#' && (!i || add_buf[i - 1] == ' '))
		{
			add_buf[i] = '\0';
			break;
		}
}

