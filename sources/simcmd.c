/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 06:32:13 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/25 14:58:39 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Create empty command.
**	Return: allocated memory with t_simcmd or NULL if allocation failed
*/

t_simcmd	*create_simcmd(void)
{
	t_simcmd	*new_simcmd;

	if (!(new_simcmd = (t_simcmd*)malloc(sizeof(t_simcmd))))
	{
		errno = ENOMEM;
		return (NULL);
	}
	new_simcmd->argc = 0;
	new_simcmd->argv = NULL;
	new_simcmd->argv_list = NULL;
	new_simcmd->buildin = EXTERNAL;
	return (new_simcmd);
}

void		delete_simcmd(void *content)
{
	t_simcmd	*simcmd;
	int			i;

	simcmd = (t_simcmd*)content;
	i = 0;
	while (i < simcmd->argc)
	{
		free(simcmd->argv[i]);
		i++;
	}
	free(simcmd->argv);
	ft_dlst_clear(&simcmd->argv_list, delete_word_desc);
	free(simcmd);
}

/*
**	Insert argument into command argumets field.
**	Return: 0 if insertion done and -1 otherwise.
*/

int			add_arg(t_simcmd *simcmd, char *arg)
{
	char	**tmp;
	int		error;

	error = 0;
	if (simcmd->argv == NULL)
	{
		if (!(simcmd->argv = (char**)ft_calloc(sizeof(char*), 2)))
			error = ALLOCATION_ERROR;
		if (!error)
			simcmd->argv[0] = arg;
	}
	else if (!error && !(tmp = enlarge(simcmd->argc, simcmd->argv, arg)))
		error = ALLOCATION_ERROR;
	if (!error)
		simcmd->argc++;
	if (!error && simcmd->argc > 1)
		simcmd->argv = tmp;
	if (error)
		free(arg);
	if (error)
	{
		errno = ENOMEM;
		return (ALLOCATION_ERROR);
	}
	return (SUCCESSED);
}
