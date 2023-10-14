#include "shell.h"

/**
 * display_history - Displays the history list, one command per line, with line numbers.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int display_history(info_t *info)
{
    print_list(info->history);
    return 0;
}

/**
 * unset_alias - Unsets an alias by setting it to an empty string.
 * @info: Parameter struct.
 * @alias_str: The alias to unset.
 * Return: 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *alias_str)
{
    char *equals_sign, saved_char;
    int ret;

    equals_sign = _strchr(alias_str, '=');
    if (!equals_sign)
        return 1;

    saved_char = *equals_sign;
    *equals_sign = '\0';

    ret = delete_node_at_index(&(info->alias),
        get_node_index(info->alias, node_starts_with(info->alias, alias_str, -1)));

    *equals_sign = saved_char;
    return ret;
}

/**
 * set_alias - Sets an alias to a string.
 * @info: Parameter struct.
 * @alias_str: The alias string.
 * Return: 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *alias_str)
{
    char *equals_sign, *alias_name;

    equals_sign = _strchr(alias_str, '=');
    if (!equals_sign)
        return 1;

    alias_name = alias_str;

    if (*equals_sign)
        return unset_alias(info, alias_str);

    unset_alias(info, alias_str);
    return (add_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 * print_single_alias - Prints a single alias string.
 * @node: The alias node.
 * Return: 0 on success, 1 on error.
 */
int print_single_alias(list_t *node)
{
    char *alias_name = NULL, *alias_value = NULL;
    char *equals_sign;

    if (node)
    {
        equals_sign = _strchr(node->str, '=');
        for (alias_name = node->str; alias_name <= equals_sign; alias_name++)
            _putchar(*alias_name);
        _putchar('\'');
        _puts(equals_sign + 1);
        _puts("'\n");
        return 0;
    }
    return 1;
}

/**
 * alias_command - Mimics the alias builtin (man alias).
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int alias_command(info_t *info)
{
    int i = 0;
    char *alias_name = NULL;
    list_t *alias_node = NULL;

    if (info->argc == 1)
    {
        alias_node = info->alias;
        while (alias_node)
        {
            print_single_alias(alias_node);
            alias_node = alias_node->next;
        }
        return 0;
    }

    for (i = 1; info->argv[i]; i++)
    {
        alias_name = _strchr(info->argv[i], '=');
        if (alias_name)
            set_alias(info, info->argv[i]);
        else
            print_single_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return 0;
}
