/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:57:45 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/20 15:45:39 by kdustin          ###   ########.fr       */
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

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	char	*s1_sp;
	char	*s1_ep;

	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	if (!(s1_sp = ft_strdup(s1 + i)))
		return (NULL);
	len = ft_strlen(s1_sp);
	s1_ep = (s1_sp + len);
	while (s1_ep != s1_sp && ft_strchr(set, *s1_ep))
		s1_ep--;
	*(s1_ep + 1) = '\0';
	return (s1_sp);
}
