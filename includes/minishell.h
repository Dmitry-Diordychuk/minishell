/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:02:02 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/25 16:37:57 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>
# include <dirent.h>
# include <limits.h>
# include <stdio.h>
# include <sys/wait.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <string.h>

/*
** Signal
*/

# define SIGMOD_DEFAULT	0
# define SIGMOD_SHELL	1
# define SIGMOD_WAIT	2

int						g_exit_status;

void					set_signals(int mode);

/*
**	Array
*/

void					free_array(char **args);
char					**enlarge(int len, char **a, char *new_arg);
int						array_len(char **a);

/*
**	History
*/

typedef struct			s_record
{
	int					len;
	char				*str;
	int					len_copy;
	char				*str_copy;
}						t_record;

int						add_record(t_dlist **history, const char *str);
void					delete_record(void *content);
int						save_str(t_record *record);
int						reset_str(t_record *record);
int						record_addchar(t_record *record, char new_char);
int						record_insertchar(t_record *record, int curpos, char c);
void					record_deletechar(t_record *record, int cur_pos);

/*
**	Enviroment
*/

typedef struct			s_env
{
	char				**envs;
	int					last_return;
	t_bool				is_exit;
}						t_env;

int						init_env(char **envp, t_env *env);
int						add_env_var(char ***envs, char *name, char *value);
char					*find_env_var(char **envp, char *name);

/*
**	Readline
*/

static char				g_term_buffer[2048];

# define ON				1
# define OFF			0
# define UP				1
# define DOWN			2
# define LEFT			3
# define RIGHT			4
# define CTRL_D			'\x04'

int						readline(char **output, t_dlist **history, t_env *env);

int						apply_func(t_dlist **history,
												int (*fun)(t_record *record));

int						init_terminal_data();
int						set_terminal_options(int on_off_define);

/*
**	Keys
*/

# define KEY_UP			"\eOA"
# define KEY_DOWN		"\eOB"
# define KEY_LEFT		"\eOD"
# define KEY_RIGHT		"\eOC"

int						backspace_key(t_dlist **cur_record, int *cur_pos);
int						special_keys(t_dlist **cur_record, int *cur_pos);
int						up_down_arrows(t_dlist **currecord, int *curpos, int d);
int						plain_keys(t_dlist **cur_record, int *cur_pos, char ch);
int						signal_c_key(t_dlist **cur_record, t_dlist **history,
																int *cur_pos);
int						left_right_keys(t_dlist **cur_record, int *cur_pos,
																int direction);

/*
**	Word descriptro and doubly linked list
*/

typedef struct			s_worddesc
{
	char				*word;
	int					flags;
}						t_worddesc;

t_worddesc				*create_word(char *word, int flags);
int						add_word(t_dlist **word_list, char *word, int flags);
void					delete_word_desc(void *content);
int						peek_word(t_dlist *word_list);
char					*pop_word();

/*
**	Lexer
*/

int						run_lexer(t_dlist **wordlist, char *input_line);
int						add_letter(char **str, char c);
int						turn_on(int *attach_flag);
int						handle_backslash(char **word, char **input_line);

int						recognize_dollar(t_dlist **wordlist, char **input_line,
													int flag, int *attach_flag);
int						recognize_operator(t_dlist **wordlist,
															char **input_line);
int						recognize_default(t_dlist **wordlist, char **input_line,
															int *attach_flag);
int						recognize_single_quote(t_dlist **wordlist,
										char **input_line, int *attach_flag);
int						recognize_double_quote(t_dlist **wordlist,
										char **input_line, int *attach_flag);

void					wind_off(char **input_line);
int						turn_on(int *attach_flag);

/*
**	Operators
*/

# define OPERATOR		0x01
# define SEPARATOR		0x02
# define PIPE			0x04
# define LESS			0x08
# define GREAT			0x10
# define GREATGREAT		0x20

/*
**	Words
*/

# define WORD			0x40
# define DOLLAR			0x80
# define DEFAULT		0x100
# define DQUOTE			0x200
# define SQUOTE			0x400
# define CLOSED			0x800
# define ATTACH			0x1000

char					*glue_words(t_dlist **wordlist, char **envp,
															int *last_return);

/*
**	Simple commands
*/

typedef struct			s_simcmd
{
	int					argc;
	char				**argv;
	t_dlist				*argv_list;
	int					buildin;
}						t_simcmd;

# define EXTERNAL		0
# define BUILD_ECHO		1
# define BUILD_CD		2
# define BUILD_PWD		3
# define BUILD_EXPORT	4
# define BUILD_UNSET	5
# define BUILD_ENV		6
# define BUILD_EXIT		7

t_simcmd				*create_simcmd(void);
void					free_simcmd(t_simcmd *simcmd);
void					delete_simcmd(void *content);
int						add_arg(t_simcmd *simcmd, char *arg);

/*
** Command table structures.
*/

typedef struct			s_cmdtbl
{
	t_dlist				*rows;
	t_bool				is_append;
	char				*out_file;
	t_dlist				*out_file_list;
	char				*in_file;
	t_dlist				*in_file_list;
}						t_cmdtbl;

t_cmdtbl				*create_cmdtbl();
void					delete_cmdtbl(t_cmdtbl *cmdtbl);
int						add_simcmd(t_cmdtbl **table);

/*
**	Expand
*/

int						run_expansion(t_cmdtbl **table, t_env *env);

/*
**	Execute
*/

typedef struct			s_fd
{
	int					out;
	int					in;
	int					tmpout;
	int					tmpin;
}						t_fd;

int						execute(t_cmdtbl *table, t_env *env);

int						setup_fd(t_bool is_last, t_fd *fd, char *out_file,
																int is_append);
int						restore_fd(t_fd *fd);
int						init_fd(t_fd *fd, char *in_file);

/*
**	Parser
*/

# define FILE_SEPARATOR	0x2000

int						run_parser(t_dlist **wordlist, t_cmdtbl **table);

int						command(t_dlist **wordlist, t_cmdtbl **table);
int						error_handler(t_dlist **wordlist);

t_bool					pass_words(t_dlist **wordlist, t_dlist **list);
int						io_redirect(t_dlist **wordlist, t_cmdtbl **table);
int						filename(t_dlist **wordlist, t_cmdtbl **table);

/*
**	Buldin
*/

int						buildin_echo(int argc, char **argv);
int						buildin_cd(int argc, char **argv, t_env *env);
int						buildin_pwd();
int						buildin_export(int argc, char **argv, t_env *env);
int						buildin_unset(int argc, char **argv, t_env *env);
int						buildin_env(t_env *env);
int						buildin_exit(int argc, char **argv, t_env *env);

void					print_declare_x(char *s1, char *s2);
char					**buildin_unset2(char *argv, char **env, int len);
void					export_sort_print(char **env);
char					**ar_free(char **ne, int size);
int						ft_strcmp_int(char *s1, char *s2);
int						ft_strchr_int(char *s, int c);
int						len_env(char **env);

/*
**	Error handling.
*/

# define SUCCESSED			0
# define ERROR				-1
# define ALLOCATION_ERROR	-2
# define TOKEN_ERROR		-3
# define READ_LINE_ERROR	-4

void					msg(char *mes1, char *mes2, char *mes3);
int						free_data(int ret);

/*
**	File.c
*/

int						extend_path(char *filename, char **path);
t_bool					check_existence(char *path, char *filename);
int						create_file(char *file, int mode, int chmod);
t_bool					check_full_path(char *program_name);
char					**splite_path(char **envp);
char					*search_in_path(char *name, char **envp);
char					*find_program(char *program_name, char **envp);
t_bool					check_dir_path(char *path);

/*
**	Data
*/

# define SET			0
# define GET			1

typedef struct			s_data
{
	char				*input_line;
	t_env				*env;
	t_dlist				*history;
	t_cmdtbl			*table;
	t_dlist				*wordlist;
}						t_data;

void					data_container(int set_get, t_data *ret_data);

#endif
