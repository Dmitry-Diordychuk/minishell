/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:02:09 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/30 23:07:50 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_handler(char **input, t_list **tokens, t_list **commands, int return_code)
{
	if (input != NULL)
	{
		free(*input);
		*input = NULL;
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

int main(void)
{
	int		gnl_ret;
	char	*input;
	t_list	*tokens;
	t_list	*commands;

	input = NULL;
	ft_putstr_fd("minishell$ ", 1);
	while ((gnl_ret = get_next_line(1, &input)) >= 0)
	{
		if (*input == '\0')
		{
			ft_putstr_fd("exit\n", 1);
			exit(free_handler(&input, NULL, NULL, 0));
		}
		if (!(tokens = run_lexer(input)))
			return (free_handler(&input, &tokens, NULL, ALLOCATION_FAILED));
		if (!(commands = run_parser(tokens)))
			return (free_handler(&input, &tokens, &commands, ALLOCATION_FAILED));
		ft_putstr_fd("\n", 1);
		while (commands != NULL)
		{
			if (execute(commands->content) == ALLOCATION_FAILED)
				return (free_handler(&input, &tokens, &commands, -1));
			commands = commands->next;
		}
		free_handler(&input, NULL, &commands, ONLYFREE);
		ft_putstr_fd("minishell$ ", 1);
	}
	return (free_handler(&input, &tokens, &commands, SUCCESSED));
}
