/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 22:22:20 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/10 22:38:42 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	The strpbrk() function locates in the null-terminated string s the first oc-
**	currence of any character in the string charset and returns a pointer to
**	this character. If no characters from charset occur anywhere in s strpbrk()
**	returns NULL.
*/

char	*ft_strpbrk(const char *s, const char *charset)
{
	int		i;
	int		j;

	i = 0;
	while (s[i] != '\0')
	{
		j = 0;
		while (charset[j] != '\0')
		{
			if (s[i] == charset[j])
				return ((char*)(s + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
