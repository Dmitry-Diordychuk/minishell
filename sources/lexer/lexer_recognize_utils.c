/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_recognize_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 21:45:00 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/24 21:45:06 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			add_letter(char **str, char c)
{
	size_t	i;
	char	*newstr;
	size_t	len;

	errno = ENOMEM;
	if (*str != NULL)
		len = ft_strlen(*str) + 2;
	else
		len = 2;
	if (!(newstr = (char*)malloc(len * sizeof(char))))
		return (ERROR);
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
	errno = 0;
	return (SUCCESSED);
}

int			handle_backslash(char **word, char **input_line)
{
	(*input_line)++;
	if (**input_line == '\0')
	{
		errno = EIO;
		msg("minishell: syntax error near unexpected token `newline'\n", 0, 0);
		return (ERROR);
	}
	add_letter(word, **input_line);
	(*input_line)++;
	return (errno ? ERROR : SUCCESSED);
}

void		wind_off(char **input_line)
{
	while (ft_isspace(**input_line))
		(*input_line)++;
}

int			turn_on(int *attach_flag)
{
	int temp;

	temp = *attach_flag;
	*attach_flag = ATTACH;
	return (temp);
}
