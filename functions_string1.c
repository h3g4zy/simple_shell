#include "shell.h"

/**
 * custom_strlen - Calculate the length of a string.
 * @str: The string to find the length of.
 *
 * Return: The length of the string.
 */
int custom_strlen(char *str)
{
    int length = 0;

    if (!str)
        return (0);

    while (str[length])
        length++;

    return (length);
}

/**
 * custom_strcmp - Compare two strings lexicographically.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: 0 if the strings are equal, a positive number if str1 > str2, or a negative number if str1 < str2.
 */
int custom_strcmp(char *str1, char *str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }

    return (*str1 - *str2);
}

/**
 * custom_starts_with - Check if a string starts with a given substring.
 * @str: The string to search.
 * @prefix: The prefix to find.
 *
 * Return: A pointer to the character in `str` where `prefix` starts or NULL if `prefix` is not found.
 */
char *custom_starts_with(char *str, char *prefix)
{
    while (*prefix)
    {
        if (*str != *prefix)
            return (NULL);

        str++;
        prefix++;
    }

    return (char *)str;
}

/**
 * custom_strcat - Concatenate two strings.
 * @dest: The destination buffer.
 * @src: The source buffer.
 *
 * Return: A pointer to the destination buffer.
 */
char *custom_strcat(char *dest, char *src)
{
    char *result = dest;

    while (*dest)
        dest++;

    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0'; // Null-terminate the result.

    return result;
}
