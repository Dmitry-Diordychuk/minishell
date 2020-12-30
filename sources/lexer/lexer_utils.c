/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 11:21:49 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/29 22:00:25 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_letter(char **str, char c)
{
	size_t	i;
	char	*newstr;
	size_t len;

	if (*str != NULL)
		len = ft_strlen(*str) + 2;
	else
		len = 2;
	if (!(newstr = (char*)malloc(len * sizeof(char))))
		return (ALLOCATION_FAILED);
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

int	get_word(char **src, char **dest, int quote)
{
	if (*src != NULL)
	{
		if (quote != CLOSE)
			if (!(*dest = ft_strdup(*src)))
				return (ALLOCATION_FAILED);
		if (quote == CLOSE)
			if (!(*dest = ft_strtrim(*src, " ")))
				return (ALLOCATION_FAILED);
		free(*src);
		*src = NULL;
		if (**dest == '\0')
		{
			free (*dest);
			return (FAILED);
		}
		return (SUCCESSED);
	}
	return (FAILED);
}
