/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 02:06:27 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/09 23:58:23 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The bzero() function writes n zeroed bytes to the string s. If n is zero,
** bzero() does nothing.
*/

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*p;

	if (n != 0)
	{
		p = (char*)s;
		i = 0;
		while (i < n)
		{
			p[i] = 0;
			i++;
		}
	}
}
