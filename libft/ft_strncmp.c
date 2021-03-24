/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 00:33:39 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/10 01:09:39 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The strncmp() function lexicographically compares the null-terminated strings
** s1 and s2.
**
** The strncmp() function compares not more than n characters. Because strncmp()
** is designed for comparing strings rather than binary data, characters that
** appear after a `\0' character are not compared.
**
** RETURN VALUES
** The strncmp() function returns an integer greater than, equal to, or less
** than 0, according as the string s1 is greater than, equal to, or less than
** the string s2. The comparison is done using unsigned characters, so that
** `\200' is greater than `\0'.
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0' && i < (n - 1))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
