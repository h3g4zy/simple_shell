#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * 
 * Return: -1 on error, otherwise the converted number
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return -1;
		}
		else
			return -1;
	}

	return result;
}

/**
 * print_error - prints an error message
 * @info: the parameter and return info struct
 * @error_string: string containing specified error type
 */
void print_error(info_t *info, char *error_string)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_string);
}

/**
 * print_d - prints a decimal (integer) number (base 10)
 * @input: the input number
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters printed
 */
int print_d(int input, int fd)
{
	int (*output_char)(char) = _putchar;
	int i, count = 0;
	unsigned int abs_value, current;

	if (fd == STDERR_FILENO)
		output_char = _eputchar;

	if (input < 0)
	{
		abs_value = -input;
		output_char('-');
		count++;
	}
	else
	{
		abs_value = input;
	}

	current = abs_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_value / i)
		{
			output_char('0' + current / i);
			count++;
		}
		current %= i;
	}

	output_char('0' + current);
	count++;

	return count;
}

/**
 * convert_number - converts a number to a string
 * @num: the number
 * @base: the base
 * @flags: argument flags
 *
 * Return: the string representation of the number
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return ptr;
}

/**
 * remove_comments - replaces the first instance of '#' with '\0'
 * @buf: address of the string to modify
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}
