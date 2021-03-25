/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtbl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 06:46:16 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/25 20:51:19 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Create command table
*/

t_cmdtbl	*create_cmdtbl(void)
{
	t_cmdtbl *new_cmd;

	if (!(new_cmd = (t_cmdtbl*)malloc(sizeof(t_cmdtbl))))
	{
		errno = ENOMEM;
		return (NULL);
	}
	new_cmd->rows = NULL;
	return (new_cmd);
}

/*
**	Delete command table.
*/

void		delete_cmdtbl(t_cmdtbl *cmdtbl)
{
	if (cmdtbl == NULL)
		return ;
	ft_dlst_clear(&cmdtbl->rows, delete_simcmd);
	free(cmdtbl);
}

/*
**	Insert simple command in command table as element of command list.
**	cmdtbl - content of command list element. Type of this element if void*.
*/

int			add_simcmd(t_cmdtbl **table)
{
	t_dlist		*new_elem;
	t_simcmd	*simple_command;

	new_elem = NULL;
	simple_command = create_simcmd();
	if (!errno && !(new_elem = ft_dlst_new(simple_command)))
	{
		errno = ENOMEM;
		return (ALLOCATION_ERROR);
	}
	if (!errno)
		ft_dlst_append(&(*table)->rows, new_elem);
	return (SUCCESSED);
}
