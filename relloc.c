#include "shell.h"

char *_memset(char *s, char b, unsigned int n)
{
    unsigned int i;
    for (i = 0; i < n; i++) {
        s[i] = b;
    }
    return s;
}

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    unsigned int i;
    if (!ptr) {
        return malloc(new_size);
    }

    if (!new_size) {
        free(ptr);
        return NULL;
    }

    if (new_size == old_size) {
        return ptr;
    }

    char *p = malloc(new_size);
    if (!p) {
        return NULL;
    }

    
    for (i = 0; i < (old_size < new_size ? old_size : new_size); i++) {
        p[i] = ((char *)ptr)[i];
    }

    free(ptr);
    return p;
}

void ffree(char **pp)
{
    if (!pp) {
        return;
    }

    while (*pp) {
        free(*pp++);
    }
    free(pp);
}
