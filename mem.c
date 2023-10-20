#include "shell.h"

/**
 * bfree - Frees a pointer and sets the address to NULL.
 *
 * @ptr: A pointer to the address to free.
 *
 * Return: 1 if the memory was freed, otherwise 0.
 */
int bfree(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
        return 1;
    }
    return 0;
}
