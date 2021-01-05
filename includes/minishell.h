/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:02:02 by kdustin           #+#    #+#             */
/*   Updated: 2021/01/05 14:21:18 by kdustin          ###   ########.fr       */
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

/*
**	Error handling.
*/

# define NONE 0
# define SUCCESSED 0
# define FAILED 1
# define ALLOCATION_FAILED -1

void error(char *message);

/*
**	Command table structures.
*/

typedef struct			s_sim_cmd
{
	int					argc;
	char				**argv;
	int					is_append;
	char				*out_file;
	char				*in_file;
}						t_sim_cmd;

t_sim_cmd				*create_sim_cmd();
void					delete_sim_command(void *content);
int						insert_arg(t_sim_cmd *sim_cmd, char *arg);

typedef struct			s_cmd
{
	t_list				*sim_cmds;
}						t_cmd;

t_cmd					*g_cur_cmd;
t_sim_cmd				*g_cur_sim_cmd;

int						add_command(t_list **command);
void					delete_command(void *content);
int						insert_sim_cmd(t_cmd *cmd, t_sim_cmd *sim_cmd);
void					free_array(char **args);
char					**enlarge(int len, char **a, char *new_arg);
int						array_len(char **a);
int						execute(t_cmd *command);

/*
**	Lexer
*/

# define STRONG_OPEN 256
# define WEAK_OPEN 257
# define SLASH_OPEN 258
# define SLASH_WEAK_OPEN 259
# define CLOSE 260
# define ENV_WEAK_OPEN 261

typedef struct	s_token
{
	char*		value;
	int			name;
}				t_token;

t_list	*run_lexer(const char *input);

/*
**	token.c
*/

int		add_token(t_list **tokens, int name, char *value);
void	delete_token(void *content);
int		try_add_word_token(t_list **tokens, char **tmp, int quote);

# define SEPARATOR 59
# define STRONG_QUOTE 39
# define WEAK_QUOTE 34
# define LESS 60
# define GREAT 62
# define GREATGREAT 63
# define PIPE 124
# define LAST_RESULT 37
# define ENV 36
# define WORD 127
# define ERROR 32
# define BLANK 33

/*
**	lexer_utils.c
*/

int	add_letter(char **str, char c);
int	get_word(char **src, char **dest, int quote);

/*
**	Parser
*/

int	run_parser(t_list *tokens, t_list **result);

/*
**	Buldin
*/

int		ft_echo (char **arg);
void	ft_exit(char **arg, int argc);
int		ft_pwd(char **args);
int		ft_env(void);
int		g_exit;


/*
**	Enviroment
*/

typedef struct	s_env_var
{
	char		*name;
	char		*value;
}				t_env_var;

char			**g_env_vars;
int				g_last_result;

int				add_env_var(char ***envs, char *name, char *value);
int				find_env_var(char **envp, char *name, char **result);

#define ONLYFREE 512

#endif
