#include "shell.h"

/**
 * is_chain_delimiter - Tests if the current character in the buffer is a chain delimiter.
 * @info: The parameter structure.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 *
 * Return: 1 if it's a chain delimiter, 0 otherwise.
 */
int is_chain_delimiter(info_t *info, char *buf, size_t *p)
{
    size_t j = *p;

    if (buf[j] == '|' && buf[j + 1] == '|')
    {
        buf[j] = 0;
        j++;
        info->cmd_buf_type = CMD_OR;
    }
    else if (buf[j] == '&' && buf[j + 1] == '&')
    {
        buf[j] = 0;
        j++;
        info->cmd_buf_type = CMD_AND;
    }
    else if (buf[j] == ';') /* Found the end of this command */
    {
        buf[j] = 0; /* Replace semicolon with null */
        info->cmd_buf_type = CMD_CHAIN;
    }
    else
    {
        return 0;
    }
    *p = j;
    return 1;
}

/**
 * check_chain - Checks whether we should continue chaining based on the last status.
 * @info: The parameter structure.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 * @i: Starting position in buf.
 * @len: Length of buf.
 *
 * Return: Void.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    if (info->cmd_buf_type == CMD_AND)
    {
        if (info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }
    if (info->cmd_buf_type == CMD_OR)
    {
        if (!info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }

    *p = j;
}

/**
 * substitute_alias - Replaces an alias in the tokenized string.
 * @info: The parameter structure.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int substitute_alias(info_t *info)
{
    int i;
    list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = node_starts_with(info->alias, info->arguments[0], '=');
        if (!node)
        {
            return 0;
        }
        free(info->arguments[0]);
        p = _strchr(node->str, '=');
        if (!p)
        {
            return 0;
        }
        p = _strdup(p + 1);
        if (!p)
        {
            return 0;
        }
        info->arguments[0] = p;
    }
    return 1;
}

/**
 * substitute_vars - Replaces variables in the tokenized string.
 * @info: The parameter structure.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int substitute_vars(info_t *info)
{
    int i = 0;
    list_t *node;

    for (i = 0; info->arguments[i]; i++)
    {
        if (info->arguments[i][0] != '$' || !info->arguments[i][1])
        {
            continue;
        }

        if (!_strcmp(info->arguments[i], "$?"))
        {
            substitute_string(&(info->arguments[i]), _strdup(convert_number(info->status, 10, 0)));
            continue;
        }
        if (!_strcmp(info->arguments[i], "$$"))
        {
            substitute_string(&(info->arguments[i]), _strdup(convert_number(getpid(), 10, 0)));
            continue;
        }
        node = node_starts_with(info->environment, &info->arguments[i][1], '=');
        if (node)
        {
            substitute_string(&(info->arguments[i]), _strdup(_strchr(node->str, '=') + 1));
            continue;
        }
        substitute_string(&info->arguments[i], _strdup(""));
    }
    return 0;
}

/**
 * substitute_string - Replaces a string.
 * @old: Address of the old string.
 * @new: New string.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int substitute_string(char **old, char *new)
{
    free(*old);
    *old = new;
    return 1;
}
