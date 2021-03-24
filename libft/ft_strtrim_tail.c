/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_tail.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 23:51:54 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/14 00:33:57 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_tail(char const *s1, char const *set)
{
	const char	*p;
	char		*res;

	if (s1 != NULL && set != NULL)
	{
		p = s1;
		while (*p != '\0')
			p++;
		p--;
		while (ft_isset(*p, set) && p != s1)
			p--;
		p++;
		if (!(res = ft_strdup_between(s1, p)))
			return (NULL);
		return (res);
	}
	return (NULL);
}
