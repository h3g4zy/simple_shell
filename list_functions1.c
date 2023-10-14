#include "shell.h"

/**
 * custom_list_length - determines length of a linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t custom_list_length(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}
	return count;
}

/**
 * custom_list_to_strings - returns an array of strings from the list
 * @head: pointer to the first node
 *
 * Return: an array of strings
 */
char **custom_list_to_strings(list_t *head)
{
	list_t *current_node = head;
	size_t list_size = custom_list_length(head);
	size_t index;
	char **strings;
	char *string;

	if (!head || !list_size)
		return NULL;

	strings = malloc(sizeof(char *) * (list_size + 1));
	if (!strings)
		return NULL;

	for (index = 0; current_node; current_node = current_node->next, index++)
	{
		string = malloc(_strlen(current_node->str) + 1);
		if (!string)
		{
			for (size_t j = 0; j < index; j++)
				free(strings[j]);
			free(strings);
			return NULL;
		}

		string = _strcpy(string, current_node->str);
		strings[index] = string;
	}

	strings[index] = NULL;
	return strings;
}

/**
 * custom_print_list - prints all elements of a list_t linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t custom_print_list(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return count;
}

/**
 * custom_node_starts_with - returns a node whose string starts with a prefix
 * @head: pointer to the list head
 * @prefix: string to match
 * @c: the next character after the prefix to match
 *
 * Return: matching node or NULL
 */
list_t *custom_node_starts_with(list_t *head, char *prefix, char c)
{
	char *substring = NULL;

	while (head)
	{
		substring = starts_with(head->str, prefix);
		if (substring && ((c == -1) || (*substring == c)))
			return head;
		head = head->next;
	}
	return NULL;
}

/**
 * custom_get_node_index - gets the index of a node in the list
 * @head: pointer to the list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t custom_get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return index;
		head = head->next;
		index++;
	}
	return -1;
}
