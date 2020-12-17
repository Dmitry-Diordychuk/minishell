/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 11:18:59 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/17 11:26:56 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *create_cmd()
{
	t_cmd	*new_cmd;

	if (!(new_cmd = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	new_cmd->n_avble_sim_cmds = 0;
	new_cmd->n_sim_cmds = 0;
	new_cmd->sim_cmds = NULL;
	new_cmd->out_file = NULL;
	new_cmd->in_file = NULL;
	new_cmd->err_file = NULL;
	new_cmd->background = 0;
	return (new_cmd);
}
