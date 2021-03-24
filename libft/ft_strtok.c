/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 21:49:34 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/24 21:52:11 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *string, const char *delim)
{
	static char	*p;
	char		*start;
	char		*result;

	if (string == NULL && p == NULL)
		return (NULL);
	if (string)
		p = string;
	while (ft_strchr(delim, *p) && *p != '\0')
		p++;
	start = p;
	while (!ft_strchr(delim, *p) && *p != '\0')
		p++;
	if (*p == '\0' && start == p)
	{
		p = NULL;
		result = NULL;
	}
	if (p != NULL)
	{
		result = start;
		*p = '\0';
		p++;
	}
	return (result);
}
