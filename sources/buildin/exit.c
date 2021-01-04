/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: che <che@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 05:25:47 by kdustin           #+#    #+#             */
/*   Updated: 2021/01/02 23:03:44 by che              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int     ft_strisnum2(char *line)
{
    int	i;

	i = 0;
	if (line[0] == '-' || line[0] == '+')
		i++;
	while (line[i])
	{
		if (line[i] < '0' || line[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void		ft_exit(char **arg, int argc)
{
    int i;

	i = 0;
    if (argc > 2)
        ft_putendl_fd("minishell: exit: too many arguments", 2);
	else if (argc == 2 && ft_strisnum2(arg[1]) == 0)
    {
        g_last_result = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
    }
    else if (argc == 2)
        g_last_result = ft_atoi(arg[1]);
    // while (arg[i])
    // {
	// 	free(arg[i]);
    //     i++;
    // }
    // free(arg);
    // (void)arg;
}
