/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 02:01:04 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/23 19:32:56 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The calloc() function contiguously allocates enough space for count objects
** that are size bytes of memory each and returns a pointer to the allocated me-
** mory. The allocated memory is filled with bytes of value zero.
**
** RETURN VALUE
** If successful calloc() function returns a pointer to allocated memory.
** If there is an error, it returns a NULL pointer.
*/

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*p;

	if (!(p = malloc(size * count)))
		return (NULL);
	i = 0;
	while (i < (count * size))
	{
		p[i] = 0;
		i++;
	}
	return ((void*)p);
}
