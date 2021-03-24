/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:57:45 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/14 00:39:20 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates (with malloc(3)) and returns a copy of’s1’ with the characters
** specified in ’set’ removed from the beginning and the end of the string.
**
** RETURN VALUE
** The trimmed string. NULL if the allocation fails.
*/

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char *decup;
	char *res;

	if (s1 == NULL || set == NULL)
		return (NULL);
	if (!(decup = ft_strtrim_head(s1, set)))
		return (NULL);
	res = ft_strtrim_tail(decup, set);
	free(decup);
	return (res);
}
