/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 15:43:40 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/17 16:17:22 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Delete arguments 2d array.
*/

void		free_args(char **args)
{
	size_t i;

	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/*
**	Enlarge char** array.
*/

int			enlarge_args(t_sim_cmd *sim_cmd, char *new_arg)
{
	int		i;
	char	**result_args;

	if (!(result_args = (char**)malloc(sizeof(char*) * (sim_cmd->n_args + 2))))
		return (-1);
	i = 0;
	while (i < sim_cmd->n_args)
	{
		if (!(result_args[i] = ft_strdup(sim_cmd->args[i])))
		{
			free_args(result_args);
			return (-1);
		}
		i++;
	}
	result_args[i] = new_arg;
	result_args[++i] = NULL;
	free_args(sim_cmd->args);
	sim_cmd->args = result_args;
	return (0);
}
