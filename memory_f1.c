#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 *
 * Return: a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;

	return s;
}

/**
 * ffree - frees an array of strings
 * @array: the array of strings to free
 */
void ffree(char **array)
{
	char **ptr = array;

	if (!array)
		return;

	while (*array)
		free(*array++);

	free(ptr);
}

