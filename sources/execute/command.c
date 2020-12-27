/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 11:18:59 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/26 21:30:01 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd()
{
	t_cmd	*new_cmd;

	if (!(new_cmd = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	new_cmd->cmdc = 0;
	new_cmd->sim_cmds = NULL;
	return (new_cmd);
}

int add_command(t_list **commands)
{
	t_list	*new_elem;
	t_cmd	*new_cmd;

	if (!(new_cmd = create_cmd()))
		return (ALLOCATION_FAILED);
	if (!(new_elem = ft_lstnew((void*)new_cmd)))
	{
		free(new_cmd);
		return (ALLOCATION_FAILED);
	}
	if (*commands == NULL)
		*commands = new_elem;
	else
		ft_lstadd_front(commands, new_elem);
	//ft_lstpush(commands, new_elem);
	return (SUCCESSED);
}

int		insert_sim_cmd(t_cmd *cmd, t_sim_cmd *sim_cmd)
{
	t_list *new_elem;

	if (!(new_elem = ft_lstnew((void*)sim_cmd)))
		return (-1);
	ft_lstpush(&cmd->sim_cmds, new_elem);
	cmd->cmdc++;
	return (0);
}

