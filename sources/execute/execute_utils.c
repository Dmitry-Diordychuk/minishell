/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 15:43:40 by kdustin           #+#    #+#             */
/*   Updated: 2021/01/01 22:06:57 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	2d array len
*/

int	array_len(char **a)
{
	int len;

	len = 0;
	while (a[len] != NULL)
	{
		len++;
	}
	return (len);
}

/*
**	Delete arguments 2d array.
*/

void		free_array(char **args)
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

char	**enlarge(int len, char **a, char *new_arg)
{
	int		i;
	char	**result_args;

	if (!(result_args = (char**)malloc(sizeof(char*) * (len + 2))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (!(result_args[i] = ft_strdup(a[i])))
		{
			free_array(result_args);
			return (NULL);
		}
		i++;
	}
	result_args[i] = new_arg;
	result_args[++i] = NULL;
	return (result_args);
}
