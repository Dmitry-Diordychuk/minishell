/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 22:27:20 by kdustin           #+#    #+#             */
/*   Updated: 2021/01/02 01:27:53 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int add_env_var(char ***envs, char *name, char *value)
{
	char *join;
	char *left;
	char **tmp;

	if (!(left = ft_strjoin(name, "=")))
		return (ALLOCATION_FAILED);
	if (!(join = ft_strjoin(left, value)))
	{
		free(left);
		return (ALLOCATION_FAILED);
	}
	free(left);
	if (*envs == NULL)
	{
		*envs = (char**)ft_calloc(2, sizeof(char*));
		*envs[0] = join;
	}
	else
	{
		if (!(tmp = enlarge(array_len(*envs), *envs, join)))
		{
			free(join);
			return (ALLOCATION_FAILED);
		}
		free_array(*envs);
		*envs = tmp;
	}
	return (SUCCESSED);
}

int	find_env_var(char **envp, char *name, char **result)
{
	int		i;
	char	**split;

	i = 0;
	while (envp[i] != NULL)
	{
		if (!(split = ft_split(envp[i], '=')))
			return (ALLOCATION_FAILED);
		if (ft_strcmp(split[0], name) == 0)
		{
			free(split[0]);
			free(split[2]);
			free(split);
			*result = split[1];
			return (SUCCESSED);
		}
		free_array(split);
		i++;
	}
	return (FAILED);
}
