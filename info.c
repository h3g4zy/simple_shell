#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */
void clear_info(info_t *info)
{
	info->custom_arg = NULL;
	info->custom_argv = NULL;
	info->custom_path = NULL;
	info->custom_argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->custom_fname = av[0];
	if (info->custom_arg)
	{
		info->custom_argv = custom_strtow(info->custom_arg, " \t");
		if (!info->custom_argv)
		{

			info->custom_argv = malloc(sizeof(char *) * 2);
			if (info->custom_argv)
			{
				info->custom_argv[0] = _strdup(info->custom_arg);
				info->custom_argv[1] = NULL;
			}
		}
		for (i = 0; info->custom_argv && info->custom_argv[i]; i++)
			;
		info->custom_argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
	ffree(info->custom_argv);
	info->custom_argv = NULL;
	info->custom_path = NULL;
	if (all)
	{
		if (!info->custom_cmd_buf)
			free(info->custom_arg);
		if (info->custom_env)
			custom_free_list(&(info->custom_env));
		if (info->custom_history)
			custom_free_list(&(info->custom_history));
		if (info->custom_alias)
			custom_free_list(&(info->custom_alias));
		ffree(info->custom_environ);
		info->custom_environ = NULL;
		bfree((void **)info->custom_cmd_buf);
		if (info->custom_readfd > 2)
			close(info->custom_readfd);
		_putchar(BUF_FLUSH);
	}
}
