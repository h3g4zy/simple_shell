#include "shell.h"

/**
 * custom_add_node_start - adds a node to the start of the list
 * @head: address of pointer to the head node
 * @str: str field of the node
 * @num: node index used by history
 *
 * Return: size of the list
 */
list_t *custom_add_node_start(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return NULL;
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return NULL;
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return NULL;
		}
	}
	new_head->next = *head;
	*head = new_head;
	return new_head;
}

/**
 * custom_add_node_end - adds a node to the end of the list
 * @head: address of pointer to the head node
 * @str: str field of the node
 * @num: node index used by history
 *
 * Return: size of the list
 */
list_t *custom_add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return NULL;

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return NULL;
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return NULL;
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return new_node;
}

/**
 * custom_print_list_str - prints only the str element of a list_t linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t custom_print_list_str(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return count;
}

/**
 * custom_delete_node_at_index - deletes a node at the given index
 * @head: address of pointer to the first node
 * @index: index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int custom_delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return 0;

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return 1;
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return 1;
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return 0;
}

/**
 * custom_free_list - frees all nodes of a list
 * @head_ptr: address of pointer to the head node
 *
 * Return: void
 */
void custom_free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
