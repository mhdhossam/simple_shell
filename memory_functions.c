#include "pat.h"

/**
 **_memorycon - fills memory with a constant byte
 *@p: the pointer to the memory area
 *@b: the byte to fill *p with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memorycon(char *p, char b, unsigned int n)
{
	unsigned int m;

	for (m = 0; m < n; m++)
		p[m] = b;
	return (p);
}

/**
 * fstr - frees a string of strings
 * @ss: string of strings
 */
void fstr(char **ss)
{
	char **a = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(a);
}

/**
 * _reallocates - reallocates a block of memory
 * @pointer : pointer to previous malloc'ated block
 * @os: byte size of previous block
 * @ns: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_reallocates(void *pointer, unsigned int os, unsigned int ns)
{
	char *p;

	if (!pointer)
		return (malloc(ns));
	if (!ns)
		return (free(pointer), NULL);
	if (ns == os)
		return (pointer);

	p = malloc(ns);
	if (!p)
		return (NULL);

	os = os < ns ? os : ns;
	while (os--)
		p[os] = ((char *)pointer)[os];
	free(pointer);
	return (p);
}






/**
 * pfree - frees a pointer and NULLs the address
 * @pointer: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int pfree(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}

