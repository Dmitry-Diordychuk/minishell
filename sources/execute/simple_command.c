/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 06:32:13 by kdustin           #+#    #+#             */
/*   Updated: 2021/01/02 00:36:58 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Create empty simple command.
**	Return: allocated memory with t_sim_cmd or NULL if allocation failed
*/

t_sim_cmd	*create_sim_cmd(void)
{
	t_sim_cmd	*new_sim_cmd;

	if (!(new_sim_cmd = (t_sim_cmd*)malloc(sizeof(t_sim_cmd))))
		return (NULL);
	new_sim_cmd->argc = 0;
	new_sim_cmd->argv = NULL;
	new_sim_cmd->out_file = NULL;
	new_sim_cmd->in_file = NULL;
	new_sim_cmd->is_append = 0;
	return (new_sim_cmd);
}

void	delete_sim_command(void *content)
{
	t_sim_cmd	*sim;
	int			i;

	i = 0;
	while (i < sim->argc)
	{
		free(sim->argv[i]);
		i++;
	}
	free(sim->argv);
	free(sim->in_file);
	free(sim->out_file);
}

/*
**	Insert argument into simple command argumets field.
**	Return: 0 if insertion done and -1 otherwise.
*/

int			insert_arg(t_sim_cmd *sim_cmd, char *arg)
{
	char *arg_dup;
	char **tmp;

	if (!(arg_dup = ft_strdup(arg)))
		return (ALLOCATION_FAILED);
	if (sim_cmd->argv == NULL)
	{
		if (!(sim_cmd->argv = (char**)ft_calloc(sizeof(char*), 2)))
		{
			free(arg_dup);
			return (ALLOCATION_FAILED);
		}
		sim_cmd->argv[0] = arg_dup;
	}
	else if (!(tmp = enlarge(sim_cmd->argc, sim_cmd->argv, arg_dup)))
	{
		free(arg_dup);
		return (ALLOCATION_FAILED);
	}
	sim_cmd->argc++;
	if (sim_cmd->argc > 1)
	{
		free_array(sim_cmd->argv);
		sim_cmd->argv = tmp;
	}
	return (0);
}
