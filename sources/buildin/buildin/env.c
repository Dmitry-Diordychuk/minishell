/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: che <che@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 05:25:34 by kdustin           #+#    #+#             */
/*   Updated: 2021/01/01 19:44:10 by che              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstrn(char *s)
{
	ft_putstr_fd(s, 1);
	write(1, "\n", 1);
}

int		ft_env(t_env_var *env)
{
	while (g_env_vars && g_env_vars->next != NULL)
	{
		ft_putstrn(((t_env_var*)g_env_vars->content)->value);
		g_env_vars = g_env_vars->next;
	}
	if (env)
		ft_putstrn(env->value);
	return (1);
}