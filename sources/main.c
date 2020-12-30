/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:02:09 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/29 22:42:29 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char	*input;
	t_list	*result;
	t_list	*commands;

	input = NULL;
	ft_putstr_fd("minishell$ ", 1);
	while (get_next_line(1, &input))
	{
		result = run_lexer(input);
		commands = run_parser(result);
		ft_putstr_fd("\n", 1);
		while (commands != NULL)
		{
			execute(commands->content);
			commands = commands->next;
		}
		free(input);
		input = NULL;
		ft_lstclear(&commands, delete_command);
		result = NULL;
		commands = NULL;
		ft_putstr_fd("minishell$ ", 1);
	}
	return (0);
}
