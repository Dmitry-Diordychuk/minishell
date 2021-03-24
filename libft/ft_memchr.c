/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 22:43:49 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/10 00:30:58 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The memchr() function locates the first occurrence of c (converted to an
** unsigned char) in string s.
**
** RETURN VALUES
** The memchr() function returns a pointer to the byte located, or NULL if no
** such byte exists within n bytes.
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*p_s;

	p_s = (char*)s;
	i = 0;
	while (i < n)
	{
		if (p_s[i] == (char)c)
			return (&p_s[i]);
		i++;
	}
	return (NULL);
}
