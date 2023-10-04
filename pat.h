#ifndef PAT_H
#define PAT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM    0
#define CMD_OR      1
#define CMD_AND     2
#define CMD_CHAIN   3

/* for convert_number() */
#define CONVERT_LOWERCASE   1
#define CONVERT_UNSIGNED    2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK  0

#define HIST_FILE   ".simple_shell_history"
#define HIST_MAX    4096

extern char **environ;

/**
 * struct liststring1 - singly linked list
 * @number: the number field
 * @string: a string
 * @next: points to the next node
 */
typedef struct liststring1
{
	int number;
	char *string;
	struct liststring1 *next;
} write_t;

/**
 * struct passinfo - contains pseudo-arguments to pass into a function,
 *                  allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @locat: a string path for the current command
 * @argc: the argument count
 * @l_count: the error count
 * @error_number: the error code for exit()s
 * @lcount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @enviroment_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @command_buf: address of pointer to cmd_buf, on if chaining
 * @command_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *locat;
	int argc;
	unsigned int l_count;
	int error_number;
	int lcount_flag;
	char *fname;
	write_t *env;
	write_t *history;
	write_t *alias;
	char **environ;
	int enviroment_changed;
	int status;
	char **command_buf;
	int command_buf_type;
	int readfd;
	int histcount;
} data_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct buildin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct buildin
{
	char *type;
	int (*func)(data_t *);
} buildin_tables;

/* chc.c */
int hsh(data_t *, char **);
int find_buildin(data_t *);
void find_command(data_t *);
void fork_command(data_t *);

/* locat.c */
int is_command(data_t *, char *);
char *duplicates_chars(char *, int, int);
char *find_cmd_locat(data_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* error_str_function.c */
void _einputs(char *);
int _eputcharacter(char);
int _inputfd(char c, int fd);
int _inputsfd(char *string, int fd);

/* string_functions.c */
int _stringlength(char *);
int _stringcomparison(char *, char *);
char *begin_with(const char *, const char *);
char *_strcon(char *, char *);
char *_stringcopies(char *, char *);
char *_strduplicates(const char *);
void _input(char *);
int _putcharacter(char);
char *_strncopies(char *, char *, int);
char *_strncon(char *, char *, int);
char *_strcharacter(char *, char);
char **strwords(char *, char *);
char **strwords2(char *, char);

/* memory_functions */
char *_memorycon(char *, char, unsigned int);
void fstr(char **);
void *_reallocates(void *, unsigned int, unsigned int);
int pfree(void **);

/* more_functions.c */
int active_mode(data_t *);
int delim_char(char, char *);
int _isalpha_char(int);
int _str_conv(char *);
int _conv_string(char *);
void print_err(data_t *, char *);
int print_dec(int, int);
char *convert_number(long int, int, int);
void remove_comms(char *);

/* emu.c */
int _terminate(data_t *);
int _currdest(data_t *);
int _helpme(data_t *);
int _this_history(data_t *);
/* emu2.c */
int de_alias(data_t *, char *);
int create_alias(data_t *, char *);
int print_alias(write_t *);
int _this_alias(data_t *);

/* find_line.c module */
ssize_t gets_input(data_t *);

ssize_t read_buffers(data_t *, char *, size_t *);
int _findline(data_t *, char **, size_t *);
void blocksHandler(int);

/* data.c module */
void delete_data(data_t *);
void set_data(data_t *, char **);
void free_data(data_t *, int);

/* enviro.c module */
char *_getenviroment(data_t *, const char *);
int _myenviroment(data_t *);
int _mysetenviroment(data_t *);
int _myunsetenviroment(data_t *);
int populate_enviroment_write(data_t *);
char **get_environment(data_t *);
int _unsetenviroment(data_t *, char *);
int _setenviroment(data_t *, char *, char *);

/* file_io_functions.c */
char *gets_history_file(data_t *info);
int write_historys(data_t *info);
int reads_history(data_t *info);
int build_history_write(data_t *info, char *buf, int lcount);
int renum_history(data_t *info);

/* liststring.c module */
write_t *add_node_start(write_t **, const char *, int);
write_t *add_node_end(write_t **, const char *, int);
size_t print_write_string(const write_t *);
int clear_node_at_index(write_t **, unsigned int);
void free_write(write_t **);
size_t write_len(const write_t *);
char **write_to_strings(write_t *);
size_t print_write(const write_t *);
write_t *node_begin_with(write_t *, char *, char);
ssize_t gets_node_index(write_t *, write_t *);

/* chainz.c */
int is_chainz(data_t *, char *, size_t *);
void check_chainz(data_t *, char *, size_t *, size_t, size_t);
int swap_alias(data_t *);
int swap_var(data_t *);
int swap_str(char **, char *);

#endif /* PAT_H */

