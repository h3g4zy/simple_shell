#include "shell.h"

/**
 * freeAndNull - frees a pointer and sets it to NULL
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int freeAndNull(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return 1;
	}
	return 0;
}

/**
 * _reallocate - reallocates a block of memory
 * @ptr: pointer to previous malloc'ed block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the reallocated block
 */
void *_reallocate(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return malloc(new_size);

	if (!new_size)
	{
		free(ptr);
		return NULL;
	}

	if (new_size == old_size)
		return ptr;

	p = malloc(new_size);

	if (!p)
		return NULL;

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];

	free(ptr);
	return p;
}
