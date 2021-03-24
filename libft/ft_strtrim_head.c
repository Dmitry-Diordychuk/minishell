/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_head.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 23:39:20 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/14 00:20:51 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_head(char const *s1, char const *set)
{
	const char	*p;
	char		*res;

	if (s1 != NULL && set != NULL)
	{
		p = s1;
		while (ft_isset(*p, set) && *p != '\0')
			p++;
		if (!(res = ft_strdup(p)))
			return (NULL);
		return (res);
	}
	return (NULL);
}
