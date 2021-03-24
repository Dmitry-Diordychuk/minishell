/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 18:37:48 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/10 00:36:43 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The memmove() function copies n bytes from string src to string dest. The two
** strings may overlap; the copy is always done in a non-destructive manner.
**
** RETURN VALUES
** The memmove() function returns the original value of dest.
*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*p_dest;
	char	*p_src;

	if (n == 0)
		return (dest);
	p_dest = (char*)dest;
	p_src = (char*)src;
	i = 0;
	if (dest == src)
		return (dest);
	else if (dest < src)
		ft_memcpy(dest, src, n);
	else
	{
		i = n - 1;
		while (i > 0)
		{
			p_dest[i] = p_src[i];
			i--;
		}
		p_dest[i] = p_src[i];
	}
	return (dest);
}
