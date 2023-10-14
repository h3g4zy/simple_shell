#include "shell.h"

/**
 * buffer_input - Buffers chained commands
 * @info: Parameter struct
 * @buf: Address of buffer
 * @len: Address of length variable
 *
 * Return: Bytes read
 */
ssize_t buffer_input(info_t *info, char **buf, size_t *len)
{
    ssize_t read_bytes = 0;
    size_t len_p = 0;

    if (!*len)
    {
        free(*buf);
        *buf = NULL;
        signal(SIGINT, handle_sigint);
#if USE_GETLINE
        read_bytes = getline(buf, &len_p, stdin);
#else
        read_bytes = custom_getline(info, buf, &len_p);
#endif
        if (read_bytes > 0)
        {
            if ((*buf)[read_bytes - 1] == '\n')
            {
                (*buf)[read_bytes - 1] = '\0';
                read_bytes--;
            }
            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);
            *len = read_bytes;
            info->cmd_buf = buf;
        }
    }
    return read_bytes;
}

/**
 * get_input - Gets a line minus the newline
 * @info: Parameter struct
 *
 * Return: Bytes read
 */
ssize_t get_input(info_t *info)
{
    static char *buf;
    static size_t i, j, len;
    ssize_t read_bytes = 0;
    char **buf_p = &(info->arg), *p;

    _putchar(BUF_FLUSH);
    read_bytes = buffer_input(info, &buf, &len);
    if (read_bytes == -1)
        return -1;
    if (len)
    {
        j = i;
        p = buf + i;

        check_chain(info, buf, &j, i, len);
        while (j < len)
        {
            if (is_chain(info, buf, &j))
                break;
            j++;
        }

        i = j + 1;
        if (i >= len)
        {
            i = len = 0;
            info->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p;
        return _strlen(p);
    }

    *buf_p = buf;
    return read_bytes;
}

/**
 * read_buffer - Reads a buffer
 * @info: Parameter struct
 * @buf: Buffer
 * @i: Size
 *
 * Return: Read bytes
 */
ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
    ssize_t read_bytes = 0;

    if (*i)
        return 0;
    read_bytes = read(info->readfd, buf, READ_BUF_SIZE);
    if (read_bytes >= 0)
        *i = read_bytes;
    return read_bytes;
}

/**
 * custom_getline - Gets the next line of input from STDIN
 * @info: Parameter struct
 * @ptr: Address of pointer to buffer, preallocated or NULL
 * @length: Size of preallocated ptr buffer if not NULL
 *
 * Return: Number of bytes read
 */
int custom_getline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t read_bytes = 0, bytes_read = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        bytes_read = *length;
    if (i == len)
        i = len = 0;

    read_bytes = read_buffer(info, buf, &len);
    if (read_bytes == -1 || (read_bytes == 0 && len == 0))
        return -1;

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = _realloc(p, bytes_read, bytes_read ? bytes_read + k : k + 1);
    if (!new_p)
        return (p ? free(p), -1 : -1);

    if (bytes_read)
        _strncat(new_p, buf + i, k - i);
    else
        _strncpy(new_p, buf + i, k - i + 1);

    bytes_read += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = bytes_read;
    *ptr = p;
    return bytes_read;
}

/**
 * handle_sigint - Blocks Ctrl-C
 * @sig_num: The signal number
 *
 * Return: void
 */
void handle_sigint(__attribute__((unused)) int sig_num)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}
