/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 19:21:20 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/10 00:37:56 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The memset() function writes n bytes of value c (converted to an unsigned
** char) to the string b.
**
** RETURN VALUES
** The memset() function returns its first argument.
*/

void	*ft_memset(void *b, int c, size_t n)
{
	char	*p;
	size_t	i;

	p = (char*)b;
	i = 0;
	while (i < n)
	{
		p[i] = (char)c;
		i++;
	}
	return ((void*)p);
}
