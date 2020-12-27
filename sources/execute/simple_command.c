/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 06:32:13 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/26 21:20:07 by kdustin          ###   ########.fr       */
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
	new_sim_cmd->args = NULL;
	new_sim_cmd->out_file = NULL;
	new_sim_cmd->in_file = NULL;
	new_sim_cmd->is_append = 0;
	return (new_sim_cmd);
}

/*
**	Insert argument into simple command argumets field.
**	Return: 0 if insertion done and -1 otherwise.
*/

int			insert_arg(t_sim_cmd *sim_cmd, char *arg)
{
	char *arg_dup;

	if (!(arg_dup = ft_strdup(arg)))
		return (ALLOCATION_FAILED);
	if (sim_cmd->args == NULL)
	{
		if (!(sim_cmd->args = (char**)malloc(sizeof(char*) * 2)))
		{
			free(arg_dup);
			return (ALLOCATION_FAILED);
		}
		sim_cmd->args[0] = arg_dup;
		sim_cmd->args[1] = NULL;
	}
	else
	{
		if (enlarge_args(sim_cmd, arg_dup))
		{
			free(arg_dup);
			return (ALLOCATION_FAILED);
		}
	}
	sim_cmd->argc++;
	return (0);
}
