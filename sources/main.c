/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:02:09 by kdustin           #+#    #+#             */
/*   Updated: 2021/01/06 17:03:36 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_handler(char **input, t_list **tokens, t_list **commands, int return_code)
{
	if (input != NULL)
	{
		if (*input != NULL)
		{
			free(*input);
			*input = NULL;
		}
	}
	if (tokens != NULL)
	{
		if (*tokens != NULL)
		{
			ft_lstclear(tokens, delete_token);
			*tokens = NULL;
		}
	}
	if (commands != NULL)
	{
		if (*commands != NULL)
		{
			ft_lstclear(commands, delete_command);
			*commands = NULL;
		}
	}
	return (return_code);
}

void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\b\b  ", 2);
		ft_putstr_fd("\n1minishell$ ", 2);
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("\b\b  \b\b", 2);
	}
}

int get_envs_from_envp(char **envp)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	g_env_vars = NULL;
	while (envp[i] != NULL)
	{
		if (!(split = ft_split(envp[i], '=')))
		{
			return (ALLOCATION_FAILED);
		}
		add_env_var(&g_env_vars, split[0], split[1]);
		j = 0;
		while (split[j] != NULL)
			free(split[j++]);
		free(split);
		i++;
	}
	return (SUCCESSED);
}

int main(int argc, char **argv, char **envp)
{
	int		gnl_ret;
	char	*input;
	t_list	*tokens;
	t_list	*commands;

	if (get_envs_from_envp(envp) == ALLOCATION_FAILED)
		return (free_handler(NULL, NULL, NULL, -1));
	input = NULL;
	ft_putstr_fd("minishell$ ", 1);
	g_pid = -1;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while ((gnl_ret = get_next_line(1, &input)))
	{
		if ((tokens = run_lexer(input)) < 0)
		{
			return (free_handler(&input, &tokens, NULL, ALLOCATION_FAILED));
		}
		if ((run_parser(tokens, &commands)) < 0)
			return (free_handler(&input, &tokens, &commands, ALLOCATION_FAILED));
		while (commands != NULL)
		{
			if (execute(commands->content) == ALLOCATION_FAILED)
				return (free_handler(&input, &tokens, &commands, -1));
			commands = commands->next;
		}
		free_handler(&input, NULL, &commands, ONLYFREE);
		ft_putstr_fd("minishell$ ", 1);
	}
	ft_putstr_fd("exit\n", 1);
	return (free_handler(&input, NULL, NULL, SUCCESSED));
}
