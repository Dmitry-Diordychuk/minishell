/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 21:00:05 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/26 22:29:57 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		save_str(t_record *record)
{
	if (!(record->str_copy = ft_strdup(record->str)))
	{
		errno = ENOMEM;
		return (ERROR);
	}
	record->len_copy = record->len;
	return (SUCCESSED);
}

int		reset_str(t_record *record)
{
	if (record->str_copy == NULL)
		return (SUCCESSED);
	free(record->str);
	if (!(record->str = ft_strdup(record->str_copy)))
	{
		free(record->str_copy);
		errno = ENOMEM;
		return (ERROR);
	}
	record->len = record->len_copy;
	free(record->str_copy);
	record->str_copy = NULL;
	return (SUCCESSED);
}

int		record_addchar(t_record *record, char new_char)
{
	char		*new_str;

	if (!(new_str = (char*)ft_calloc(sizeof(char), (record->len + 2))))
	{
		errno = ENOMEM;
		return (ERROR);
	}
	ft_strcpy(new_str, record->str);
	new_str[record->len] = new_char;
	free(record->str);
	record->str = new_str;
	record->len++;
	return (SUCCESSED);
}

int		record_insertchar(t_record *record, int cur_pos, char ch)
{
	int		i;
	char	*new_str;

	if (!(new_str = (char*)ft_calloc(sizeof(char), record->len + 2)))
		return (ERROR);
	i = 0;
	while (i < cur_pos)
	{
		new_str[i] = record->str[i];
		i++;
	}
	new_str[i] = ch;
	while (record->str[i] != '\0')
	{
		new_str[i + 1] = record->str[i];
		i++;
	}
	free(record->str);
	record->str = new_str;
	record->len++;
	return (SUCCESSED);
}

void	record_deletechar(t_record *record, int cur_pos)
{
	int i;

	if (cur_pos == record->len)
		record->str[cur_pos - 1] = '\0';
	else
	{
		i = cur_pos;
		while (record->str[i] != '\0')
		{
			record->str[i - 1] = record->str[i];
			i++;
		}
		record->str[i - 1] = '\0';
	}
	record->len--;
}
