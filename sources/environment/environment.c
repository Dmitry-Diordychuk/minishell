/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 22:27:20 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/24 18:26:05 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		init_env(char **envp, t_env *env)
{
	int		i;
	int		len;

	env->envs = NULL;
	len = 0;
	while (envp[len] != NULL)
		len++;
	if (!(env->envs = (char**)calloc(len + 1, sizeof(char*))))
		errno = ENOMEM;
	i = -1;
	while (!errno && ++i < len)
		if (!(env->envs[i] = ft_strdup(envp[i])))
			errno = ENOMEM;
	if (errno)
	{
		free_array(env->envs);
		return (ERROR);
	}
	env->last_return = 0;
	env->is_exit = FALSE;
	return (SUCCESSED);
}

char	*find_env_var(char **envp, char *name)
{
	int		i;
	char	**split;
	char	*result;

	i = 0;
	while (envp[i] != NULL)
	{
		if (!(split = ft_split(envp[i], '=')))
		{
			errno = ENOMEM;
			return (NULL);
		}
		if (ft_strcmp(split[0], name) == 0)
		{
			result = split[1];
			free(split[0]);
			free(split[2]);
			free(split);
			return (result);
		}
		free_array(split);
		i++;
	}
	result = ft_strdup("");
	return (result);
}
