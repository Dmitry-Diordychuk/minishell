/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:46:26 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/24 21:03:58 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_record	*create_record(const char *str)
{
	t_record *new_record;

	if (!(new_record = (t_record*)malloc(sizeof(t_record))))
		return (NULL);
	if (!(new_record->str = ft_strdup(str)))
	{
		free(new_record);
		return (NULL);
	}
	new_record->len = ft_strlen(str);
	new_record->len_copy = -1;
	new_record->str_copy = NULL;
	return (new_record);
}

int			add_record(t_dlist **history, const char *str)
{
	t_record	*new_record;
	t_delement	elem;

	if (!(new_record = create_record(str)))
		return (ERROR);
	if (!(elem = ft_dlst_new(new_record)))
	{
		delete_record(new_record);
		return (ERROR);
	}
	ft_dlst_prepend(history, elem);
	return (SUCCESSED);
}

void		delete_record(void *content)
{
	t_record *record;

	record = (t_record*)content;
	free(record->str);
	free(record->str_copy);
	free(record);
}
