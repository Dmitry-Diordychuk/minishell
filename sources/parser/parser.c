/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:33:31 by kdustin           #+#    #+#             */
/*   Updated: 2021/01/05 23:01:06 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_token(void* container)
{
	t_token	*token;

	token = (t_token*)container;
	ft_putstr_fd("{", 1);
	if (token->name == BLANK)
		ft_putstr_fd("Blank", 1);
	else if (token->name == SEPARATOR)
		ft_putstr_fd("Separator", 1);
	else if (token->name == STRONG_QUOTE)
		ft_putstr_fd("Strong quote", 1);
	else if (token->name == WEAK_QUOTE)
		ft_putstr_fd("Weak quote", 1);
	else if (token->name == LESS)
		ft_putstr_fd("Less", 1);
	else if (token->name == GREAT)
		ft_putstr_fd("Greate", 1);
	else if (token->name == GREATGREAT)
		ft_putstr_fd("Greate greate", 1);
	else if (token->name == PIPE)
		ft_putstr_fd("Pipe", 1);
	else if (token->name == LAST_RESULT)
		ft_putstr_fd("Last result", 1);
	else if (token->name == ENV)
		ft_putstr_fd("Enviroment value", 1);
	if (token->name == WORD)
	{
		ft_putstr_fd("Word", 1);
		ft_putstr_fd(", \"", 1);
		ft_putstr_fd(token->value, 1);
		ft_putstr_fd("\"} ", 1);
	}
	else
		ft_putstr_fd(", \"\"} ", 1);
}

int	peek_token(t_list *tokens)
{
	t_token *t;

	if (tokens != NULL)
	{
		t = (t_token*)ft_lstget(tokens, 0);
		return (t->name);
	}
	return (-1);
}

t_token *pop_token(t_list **tokens)
{
	t_token	*ret;
	t_list	*tmp;

	ret = (t_token*)((*tokens)->content);
	//print_token(ret);
	if(*tokens != NULL)
	{
		tmp = (*tokens)->next;
		free(*tokens);
		*tokens = tmp;
	}
	return(ret);
}

char *pop_value(t_list **tokens)
{
	t_token	*token;
	char	*value;

	token = pop_token(tokens);
	if (!(value = ft_strdup(token->value)))
		return (NULL);
	free(token);
	return (value);
}

char *joinfree(char *s1, char *s2)
{
	char *res;

	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (NULL);
	if (!(res = ft_strjoin(s1, s2)))
		return (NULL);
	free(s1);
	free(s2);
	return (res);
}

char *find_and_concat(char *str)
{
	char *p;
	char tmp;
	char *s2;

	p = str;
	while (*p != '\0' && *p != ' ' && *p != '"' && *p != '\'' && *p != '=' && *p != '\\')
		p++;
	tmp = *p;
	if (*p != '\0')
		*p++ = '\0';
	if (find_env_var(g_env_vars, str, &s2) == ALLOCATION_FAILED)
		return (NULL);
	if (s2 != NULL)
		s2 = ft_strdup(s2);
	else
		s2 = ft_strdup("");
	if (tmp == ' ')
		s2 = joinfree(s2, ft_strdup(" "));
	else if (tmp == '"')
		s2 = joinfree(s2, ft_strdup("\""));
	else if (tmp == '\'')
		s2 = joinfree(s2, ft_strdup("'"));
	else if (tmp == '=')
		s2 = joinfree(s2, ft_strdup("="));
	else if (tmp == '\\')
		s2 = joinfree(s2, ft_strdup(""));
	if (s2 == NULL || !(p = ft_strjoin(s2, p)))
		return (NULL);
	free(s2);
	return (p);
}

char *get_str_by_type(t_token *token, int type)
{
	char *res;

	res = NULL;
	if (token == NULL && type == ENV)
		res = ft_strdup("$");
	else if (type == WORD)
		res = ft_strdup(token->value);
	else if (type == STRONG_QUOTE || type == WEAK_QUOTE)
		res = ft_strdup("");
	else if (type == LAST_RESULT)
		res = ft_itoa(g_last_result);
	else if (type == ENV)
		res = find_and_concat(token->value);
	if (res == NULL)
		return (NULL);
	return (res);
}

int	build_word(t_list **tokens, char **word)
{
	char	*tmp;
	t_token	*token;
	int		type;

	token = NULL;
	type = peek_token(*tokens);
	if (type == ENV)
	{
		while ((type = peek_token(*tokens)) == ENV)
			free(pop_token(tokens));
		type = ENV;
	}
	if (*tokens != NULL)
		token = pop_token(tokens);
	if (*word == NULL)
	{
		*word = get_str_by_type(token, type);
		if (*word == NULL)
			return (ALLOCATION_FAILED);
	}
	else
	{
		tmp = get_str_by_type(token, type);
		*word = joinfree(*word, tmp);
		if (*word == NULL)
			return (ALLOCATION_FAILED);
	}
	free(token);
	return (SUCCESSED);
}

int	check_if_word(int type)
{
	if (type == WORD || type == ENV || type == LAST_RESULT ||
		type == STRONG_QUOTE || type == WEAK_QUOTE)
		return (TRUE);
	return (FALSE);
}

int check_if_io(int type)
{
	if (type == LESS || type == GREAT || type == GREATGREAT)
		return (TRUE);
	return (FALSE);
}

int	io_file(t_list **tokens, t_sim_cmd **sim_cmd)
{
	char	*tmp;
	int		peek;
	char	buf[100];

	tmp = NULL;
	while ((peek = peek_token(*tokens)) == BLANK)
		free(pop_token(tokens));
	if (check_if_io(peek))
	{
		free(pop_token(tokens));
		while (peek_token(*tokens) == BLANK)
			free(pop_token(tokens));
		while (*tokens != NULL && peek_token(*tokens) != BLANK && peek_token(*tokens) != SEPARATOR && peek_token(*tokens) != PIPE)
			build_word(tokens, &tmp);
		if (peek == LESS)
		{
			if (!((*sim_cmd)->in_file = ft_strdup(tmp)))
				return (ALLOCATION_FAILED);
		}
		else if (peek == GREATGREAT || peek == GREAT)
		{
			if (!((*sim_cmd)->out_file = ft_strdup(tmp)))
				return (ALLOCATION_FAILED);
			open(extend_path(tmp, getcwd(buf, 100)), O_CREAT | O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
		}
		if (peek == GREATGREAT)
			(*sim_cmd)->is_append = 1;
		if (*tokens != NULL && peek_token(*tokens) != SEPARATOR && peek_token(*tokens) != PIPE)
			free(pop_token(tokens));
		free(tmp);
		return (SUCCESSED);
	}
	return (FAILED);
}

int	cmd_suffix(t_list **tokens, t_sim_cmd **sim_cmd)
{
	int		res;
	char	*tmp;

	tmp = NULL;
	while ((res = io_file(tokens, sim_cmd)) == SUCCESSED)
		if (res == ERROR)
			return (ERROR);
	if (check_if_word(peek_token(*tokens)))
	{
		while (check_if_word(peek_token(*tokens)))
		{
			while (*tokens != NULL && peek_token(*tokens) != BLANK && peek_token(*tokens) != SEPARATOR && peek_token(*tokens) != PIPE && !check_if_io(peek_token(*tokens)))
				build_word(tokens, &tmp);
			if (insert_arg(*sim_cmd, tmp) == ALLOCATION_FAILED)
			{
				free(tmp);
				return (ALLOCATION_FAILED);
			}
			if (*tokens != NULL && peek_token(*tokens) != PIPE && peek_token(*tokens) != SEPARATOR && !check_if_io(peek_token(*tokens)))
				free(pop_token(tokens));
			free(tmp);
			tmp = NULL;
		}
	}
	return (SUCCESSED);
}

int	cmd_prefix(t_list **tokens, t_sim_cmd **sim_cmd)
{
	int	io_res;

	while ((io_res = io_file(tokens, sim_cmd)) == SUCCESSED)
		if (io_res == ERROR)
			return (ERROR);
	return (SUCCESSED);
}

int	command(t_list **tokens, t_list **cmds)
{
	t_sim_cmd	*sim_cmd;
	char		*tmp;

	tmp = NULL;
	sim_cmd = create_sim_cmd();
	if (cmd_prefix(tokens, &sim_cmd) == ERROR)
		return (ERROR);
	if (check_if_word(peek_token(*tokens)))
	{
		while (*tokens != NULL && peek_token(*tokens) != BLANK && peek_token(*tokens) != SEPARATOR && peek_token(*tokens) != PIPE)
		{
			if (peek_token(*tokens) == STRONG_QUOTE && peek_token(*tokens) == WEAK_QUOTE)
			{
				free(pop_token(tokens));
				continue;
			}
			build_word(tokens, &tmp);
		}
		if (insert_arg(sim_cmd, tmp) == ALLOCATION_FAILED)
		{
			free(tmp);
			return (ALLOCATION_FAILED);
		}
		free(tmp);
		if (peek_token(*tokens) == BLANK)
		{
			free(pop_token(tokens));
			while (check_if_word(peek_token(*tokens)) || check_if_io(peek_token(*tokens)))
				if (cmd_suffix(tokens, &sim_cmd) == ERROR)
					return (ERROR);
		}
	}
	insert_sim_cmd((t_cmd*)(ft_lstlast(*cmds)->content), sim_cmd);
	return (SUCCESSED);
}

int	pipe_sequence(t_list **tokens, t_list **cmds)
{
	int	peek;

	while ((peek = peek_token(*tokens)) == BLANK)
		free(pop_token(tokens));
	if (peek == PIPE)
	{
		free(pop_token(tokens));
		if (command(tokens, cmds) == ERROR)
			return (ERROR);
		if (pipe_sequence(tokens, cmds) == ERROR)
			return (ERROR);
	}
	else if (peek != SEPARATOR && peek != -1)
	{
		if (command(tokens, cmds) == ERROR)
			return (ERROR);
		if (peek_token(*tokens) == PIPE)
			if (pipe_sequence(tokens, cmds) == ERROR)
				return (ERROR);
	}
	return (SUCCESSED);
}

int	list(t_list **tokens, t_list **cmds)
{
	if (peek_token(*tokens) == SEPARATOR)
	{
		free(pop_token(tokens));
		if (add_command(cmds) == ALLOCATION_FAILED)
			return (ALLOCATION_FAILED);
		if (pipe_sequence(tokens, cmds) == ERROR)
			return (ERROR);
		if (list(tokens, cmds) == ERROR)
			return (ERROR);
	}
	else if (peek_token(*tokens) != -1)
	{
		if (add_command(cmds) == ALLOCATION_FAILED)
			return (ALLOCATION_FAILED);
		if (pipe_sequence(tokens, cmds) == ERROR)
			return (ERROR);
		if (list(tokens, cmds) == ERROR)
			return (ERROR);
	}
	return (SUCCESSED);
}

int	complete_command(t_list **tokens, t_list **cmds)
{
	if (list(tokens, cmds) == ERROR)
		return (ERROR);
	if (peek_token(*tokens) == SEPARATOR)
		free(pop_token(tokens));
	return (SUCCESSED);
}

int run_parser(t_list *tokens, t_list **result)
{
	*result = NULL;
	if (complete_command(&tokens, result) == ERROR)
		return (ALLOCATION_FAILED);
	return (SUCCESSED);
}
