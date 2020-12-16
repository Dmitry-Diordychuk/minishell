/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 23:42:17 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/10 01:17:16 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The strnstr() function locates the first occurrence of the null-terminated
** string s2 in the string s1, where not more than n characters are searched.
** Characters that appear after a `\0' character are not searched.
**
** RETURN VALUES
** If s2 is an empty string, s1 is returned; if needle occurs nowhere in s1,
** NULL is returned; otherwise a pointer to the first character of the first
** occurrence of s2 is returned.
*/

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s2[0] == '\0')
		return ((char*)s1);
	while (s1[i] != '\0' && n != 0 && i < n)
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			while (s1[i + j] == s2[j] && s2[j] != '\0' && (i + j) < n)
				j++;
			if (s2[j] == '\0')
				return ((char*)&s1[i]);
		}
		i++;
	}
	return (NULL);
}
