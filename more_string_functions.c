#include "shell.h"

/**
 * custom_puts_stderr - custom implementation to print a string to stderr
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void custom_puts_stderr(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		custom_putchar_stderr(str[index]);
		index++;
	}
}

/**
 * custom_putchar_stderr - custom implementation to write a character to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_putchar_stderr(char c)
{
	static int buffer_index;
	static char output_buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
	{
		write(2, output_buffer, buffer_index);
		buffer_index = 0;
	}
	if (c != BUF_FLUSH)
		output_buffer[buffer_index++] = c;
	return (1);
}

/**
 * custom_putchar_fd - custom implementation to write a character to the given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_putchar_fd(char c, int file_descriptor)
{
	static int buffer_index;
	static char output_buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
	{
		write(file_descriptor, output_buffer, buffer_index);
		buffer_index = 0;
	}
	if (c != BUF_FLUSH)
		output_buffer[buffer_index++] = c;
	return (1);
}

/**
 * custom_puts_fd - custom implementation to print a string to the given file descriptor
 * @str: the string to be printed
 * @file_descriptor: the file descriptor to write to
 *
 * Return: the number of characters put
 */
int custom_puts_fd(char *str, int file_descriptor)
{
	int index = 0;

	if (!str)
		return (0);
	while (*str)
	{
		index += custom_putchar_fd(*str++, file_descriptor);
	}
	return (index);
}
