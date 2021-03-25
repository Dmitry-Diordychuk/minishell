/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_recognize_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 21:45:00 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/25 18:51:21 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			add_letter(char **str, char c)
{
	size_t	i;
	char	*newstr;
	size_t	len;

	if (*str != NULL)
		len = ft_strlen(*str) + 2;
	else
		len = 2;
	if (!(newstr = (char*)malloc(len * sizeof(char))))
	{
		errno = ENOMEM;
		return (ALLOCATION_ERROR);
	}
	i = 0;
	while (*str != NULL && (*str)[i] != '\0')
	{
		newstr[i] = (*str)[i];
		i++;
	}
	newstr[i++] = c;
	newstr[i] = '\0';
	free(*str);
	*str = newstr;
	return (SUCCESSED);
}

void		wind_off(char **input_line)
{
	while (**input_line == ' ')
		(*input_line)++;
}

int			turn_on(int *attach_flag)
{
	int temp;

	temp = *attach_flag;
	*attach_flag = ATTACH;
	return (temp);
}

int			skip_dollar(char **input_line, char **word)
{
	int error;

	(*input_line)++;
	error = add_letter(word, **input_line);
	(*input_line)++;
	return (error);
}
