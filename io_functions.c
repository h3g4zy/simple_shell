#include "shell.h"

/**
 * custom_get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */
char *custom_get_history_file(info_t *info)
{
	char *path, *directory;

	directory = _getenv(info, "HOME=");
	if (!directory)
		return (NULL);
	path = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!path)
		return (NULL);
	path[0] = 0;
	_strcpy(path, directory);
	_strcat(path, "/");
	_strcat(path, HIST_FILE);
	return (path);
}

/**
 * custom_write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int custom_write_history(info_t *info)
{
	ssize_t fd;
	char *file_name = custom_get_history_file(info);
	list_t *current_node = NULL;

	if (!file_name)
		return (-1);

	fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (fd == -1)
		return (-1);
	for (current_node = info->history; current_node; current_node = current_node->next)
	{
		_putsfd(current_node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * custom_read_history - reads history from a file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int custom_read_history(info_t *info)
{
	int i, last = 0, line_count = 0;
	ssize_t fd, read_length, file_size = 0;
	struct stat file_stat;
	char *buffer = NULL, *file_name = custom_get_history_file(info);

	if (!file_name)
		return (0);

	fd = open(file_name, O_RDONLY);
	free(file_name);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &file_stat))
		file_size = file_stat.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	read_length = read(fd, buffer, file_size);
	buffer[file_size] = 0;
	if (read_length <= 0)
		return (free(buffer), 0);
	close(fd);
	for (i = 0; i < file_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_history_list(info, buffer + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buffer + last, line_count++);
	free(buffer);
	info->histcount = line_count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds an entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @line_count: the history line count, histcount
 *
 * Return: Always 0
 */
int custom_build_history_list(info_t *info, char *buf, int line_count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, line_count);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int custom_renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
