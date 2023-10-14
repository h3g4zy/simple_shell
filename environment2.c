#include "shell.h"

/**
 * get_environ - Returns a copy of the environment variables as an array of strings.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
char **get_environ(info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        info->environ = list_to_strings(info->env);
        info->env_changed = 0;
    }

    return info->environ;
}

/**
 * unsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments.
 * @var: The environment variable to remove.
 * Return: 1 on deletion, 0 otherwise.
 */
int unsetenv(info_t *info, char *var)
{
    if (!info->env || !var)
        return 0;

    list_t *node = info->env;
    size_t i = 0;
    char *p;

    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env), i);
            i = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        i++;
    }

    return info->env_changed;
}

/**
 * setenv - Initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments.
 * @var: The environment variable name.
 * @value: The environment variable value.
 * Return: Always 0.
 */
int setenv(info_t *info, char *var, char *value)
{
    if (!var || !value)
        return 0;

    char *buf = malloc(_strlen(var) + _strlen(value) + 2);
    if (!buf)
        return 1;

    _strcpy(buf, var);
    _strcat(buf, "=");
    _strcat(buf, value);

    list_t *node = info->env;
    char *p;

    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return 0;
        }
        node = node->next;
    }

    add_node_end(&(info->env), buf, 0);
    free(buf);
    info->env_changed = 1;

    return 0;
}
