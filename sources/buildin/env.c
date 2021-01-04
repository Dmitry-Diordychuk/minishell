/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: che <che@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 05:25:34 by kdustin           #+#    #+#             */
/*   Updated: 2021/01/04 23:22:54 by che              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstrn(char *s)
{
	ft_putstr_fd(s, 1);
	write(1, "\n", 1);
}

int		ft_env(void)
{
	int	i;

	i = 0;
	while (g_env_vars && g_env_vars[i] != NULL)
	{
		ft_putstrn(g_env_vars[i]);
		i++;
	}
	return (1);
}