/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 15:43:40 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/26 20:48:30 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	2d array len
*/

int		array_len(char **a)
{
	int len;

	len = 0;
	while (a[len] != NULL)
		len++;
	return (len);
}

/*
**	Delete arguments 2d array.
*/

void	free_array(char **args)
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
	{
		free_array(a);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		result_args[i] = a[i];
		i++;
	}
	free(a);
	result_args[i] = new_arg;
	result_args[++i] = NULL;
	return (result_args);
}
