#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* hsh.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* path.c */
int is_executable(info_t *, char *);
char *copy_chars(char *, int, int);
char *find_command_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* more_string_functions.c */
void custom_puts_stderr(char *str);
int custom_putchar_stderr(char c);
int custom_putchar_fd(char c, int file_descriptor);
int custom_puts_fd(char *str, int file_descriptor);

/* functions_string1.c */
int custom_strlen(char *);
int custom_strcmp(char *, char *);
char *custom_starts_with(const char *, const char *);
char *custom_strcat(char *, char *);

/* functions_string2.c */
char *custom_strcpy(char *, char *);
char *custom_strdup(const char *);
void custom_puts(char *);
int custom_putchar(char);

/* functions_string3.c */
char *custom_strncpy(char *, char *, int);
char *custom_strncat(char *, char *, int);
char *custom_strchr(char *, char);

/* functions_string4.c */
char **custom_strtow(char *, char *);
char **custom_strtow2(char *, char);


/* memory_f1.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory_f2.c */
int bfree(void **);

/* additional_functions.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* additional_functions2.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* emu1.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* emu2.c */
int _myhistory(info_t *);
int _myalias(info_t *);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int _myalias(info_t *info);

/* line.c module */
ssize_t get_input(info_t *);
int custom_getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* info.c module */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* environment1.c module */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* environment2.c module */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* io_functions.c */
char *custom_get_history_file(info_t *info);
int custom_write_history(info_t *info);
int custom_read_history(info_t *info);
int custom_build_history_list(info_t *info, char *buf, int linecount);
int custom_renumber_history(info_t *info);

/* list_functions1.c */
size_t custom_list_len(const list_t *);
char **custom_list_to_strings(list_t *);
size_t custom_print_list(const list_t *);
list_t *custom_node_starts_with(list_t *, char *, char);
ssize_t custom_get_node_index(list_t *, list_t *);


/* list_functions2.c */
list_t *custom_add_node_start(list_t **, const char *, int);
list_t *custom_add_node_end(list_t **, const char *, int);
size_t custom_print_list_str(const list_t *);
int custom_delete_node_at_index(list_t **, unsigned int);
void custom_free_list(list_t **);

/* delimeters.c */
int is_chain_delimiter(info_t *info, char *buffer, size_t *position);
void check_chain(info_t *info, char *buffer, size_t *position, size_t startIndex, size_t bufferLength);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **oldStr, char *newStr);

#endif