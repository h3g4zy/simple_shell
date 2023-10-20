#include "shell.h"

/**
 * _myhistory - Display the command history with line numbers.
 * @info: Pointer to the info struct.
 *
 * This function displays the history list with line numbers, starting at 0.
 *
 * Return: Always 0.
 */
int _myhistory(info_t *info)
{
    print_list(info->history);
    return 0;
}

/**
 * set_alias - Set an alias for a string.
 * @info: Pointer to the info struct.
 * @str: The alias string.
 *
 * Return: 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
    char *p;

    p = _strchr(str, '=');
    if (!p)
        return 1;

    if (!*++p)
        return unset_alias(info, str);

    unset_alias(info, str);
    return add_node_end(&(info->alias), str, 0) == NULL ? 1 : 0;
}

/**
 * unset_alias - Unset an alias.
 * @info: Pointer to the info struct.
 * @str: The alias to unset.
 *
 * Return: 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
    char *p, c;
    int ret;

    p = _strchr(str, '=');
    if (!p)
        return 1;

    c = *p;
    *p = 0;
    ret = delete_node_at_index(&(info->alias), get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *p = c;
    return ret;
}

/**
 * print_alias - Print an alias string.
 * @node: The alias node to print.
 *
 * Return: 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
    char *p = NULL, *a = NULL;

    if (node) {
        p = _strchr(node->str, '=');
        for (a = node->str; a <= p; a++)
            _putchar(*a);
        _putchar('\'');
        _puts(p + 1);
        _puts("'\n");
        return 0;
    }
    return 1;
}

/**
 * _myalias - Display or set aliases.
 * @info: Pointer to the info struct.
 *
 * This function mimics the alias builtin (man alias).
 *
 * Return: Always 0.
 */
int _myalias(info_t *info)
{
    int i = 0;
    char *p = NULL;

    if (info->argc == 1) {
        list_t *node = info->alias;
        while (node) {
            print_alias(node);
            node = node->next;
        }
        return 0;
    }

    for (i = 1; info->argv[i]; i++) {
        p = _strchr(info->argv[i], '=');
        if (p)
            set_alias(info, info->argv[i]);
        else
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return 0;
}
