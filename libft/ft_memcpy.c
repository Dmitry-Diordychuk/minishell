/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 17:27:57 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/10 00:35:09 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The memcpy() function copies n bytes from memory area src to memory area
** dest. If dest and src overlap, behavior is undefined. Applications in which
** dest and src might overlap should use memmove(3) instead.
**
** RETURN VALUES
** The memcpy() function returns the original value of dest.
*/

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*p_dest;
	char	*p_src;

	if (dest == NULL && src == NULL)
		return (NULL);
	p_dest = (char*)dest;
	p_src = (char*)src;
	i = 0;
	while (i < n)
	{
		p_dest[i] = p_src[i];
		i++;
	}
	return (dest);
}
