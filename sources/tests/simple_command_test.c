/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 07:14:15 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/17 19:14:21 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_arg(char **args)
{
	size_t i;

	i = -1;
	while (args[++i] != NULL)
	{
		ft_putstr_fd(args[i], 1);
		ft_putchar_fd('\n', 1);
	}
}

int	main(void)
{
	t_sim_cmd *sim_cmd;

	sim_cmd = create_sim_cmd();

	ft_putnbr_fd(sim_cmd->argc, 1);
	ft_putchar_fd('\n', 1);
	insert_arg(sim_cmd, "test1");
	insert_arg(sim_cmd, "test2");
	insert_arg(sim_cmd, "test3");
	print_arg(sim_cmd->args);
	return (0);
}
