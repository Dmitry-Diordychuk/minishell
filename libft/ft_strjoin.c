/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 15:09:02 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/21 15:19:41 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates (with malloc(3)) and returns a newstring, which is the result of
** the concatenationof ’s1’ and ’s2’.
**
** RETURN VALUE
** The new string. NULL if the allocation fails.
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(result = (char*)ft_malloc(sizeof(char) * (len + 1), NULL)))
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (i < len)
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return (result);
}
