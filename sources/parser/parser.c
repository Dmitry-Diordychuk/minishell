/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:33:31 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/27 12:27:15 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_token(void* container)
{
	t_token	*token;

	token = (t_token*)container;
	ft_putstr_fd("{", 1);
	if (token->name == SEPARATOR)
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
	print_token(ret);
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

char *get_str_by_type(t_token *token, int type)
{
	char *res;

	res = NULL;
	if (type == WORD)
		res = ft_strdup(token->value);
	else if (type == STRONG_QUOTE || type == WEAK_QUOTE)
		res = ft_strdup("");
	else if (type == LAST_RESULT)
		res = ft_itoa(g_last_result);
	else if (type == ENV)
	{
		res = find_env_var(g_env_vars, token->value);
		if (res != NULL)
			res = ft_strdup(res);
		else
			res = ft_strdup("");
	}
	if (res == NULL)
		return (NULL);
	return (res);
}

int	build_word(t_list **tokens, char **word)
{
	char	*tmp;
	t_token	*token;
	int		type;

	type = peek_token(*tokens);
	if (type == ENV)
		type = ENV;
	if (type == ENV)
		free(pop_token(tokens));
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

int	io_file(t_list **tokens, t_sim_cmd **sim_cmd)
{
	int		tmp;
	char	*res;

	res = NULL;
	tmp = peek_token(*tokens);
	if (tmp == GREATGREAT || tmp == GREAT || tmp == LESS)
	{
		free(pop_token(tokens));
		if (build_word(tokens, &res) == ALLOCATION_FAILED)
				return (ALLOCATION_FAILED);
		if (tmp == LESS)
			(*sim_cmd)->in_file = res;
		else if (tmp == GREATGREAT || tmp == GREAT)
			(*sim_cmd)->out_file = res;
		if (tmp == GREATGREAT)
			(*sim_cmd)->is_append = 1;
		return (SUCCESSED);
	}
	return (FAILED);
}

int	check_if_word(int type)
{
	if (type == WORD || type == ENV || type == LAST_RESULT ||
		type == STRONG_QUOTE || type == WEAK_QUOTE)
		return (TRUE);
	return (FALSE);
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
			build_word(tokens, &tmp);
		if (insert_arg(*sim_cmd, tmp) == ALLOCATION_FAILED)
		{
			free(tmp);
			return (ALLOCATION_FAILED);
		}
	}
	free(tmp);
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
	int			peek;
	t_sim_cmd	*sim_cmd;
	char		*tmp;

	tmp = NULL;
	sim_cmd = create_sim_cmd();
	if (cmd_prefix(tokens, &sim_cmd) == ERROR)
		return (ERROR);
	if (check_if_word(peek_token(*tokens)))
	{
		build_word(tokens, &tmp);
		if (insert_arg(sim_cmd, tmp) == ALLOCATION_FAILED)
		{
			free(tmp);
			return (ALLOCATION_FAILED);
		}
		free(tmp);
		if (cmd_suffix(tokens, &sim_cmd) == ERROR)
			return (ERROR);
	}
	insert_sim_cmd((t_cmd*)((*cmds)->content), sim_cmd);
	return (SUCCESSED);
}

int	pipe_sequence(t_list **tokens, t_list **cmds)
{
	int	peek;

	peek = peek_token(*tokens);
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

t_list *run_parser(t_list *tokens)
{
	t_list	*cmds;

	cmds = NULL;
	if (complete_command(&tokens, &cmds) == ERROR)
		return (NULL);
	return (cmds);
}
