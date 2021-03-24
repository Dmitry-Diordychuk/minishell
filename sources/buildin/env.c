/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 05:25:34 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/20 20:58:44 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

int				buildin_env(t_env *env)
{
	char		**ne;
	int			i;

	ne = env->envs;
	i = 0;
	while (ne[i])
	{
		write(1, ne[i], ft_strlen(ne[i]));
		write(1, "\n", 1);
		i++;
	}
	return (SUCCESSED);
}
