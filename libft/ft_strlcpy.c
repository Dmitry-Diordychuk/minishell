/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 17:17:14 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/10 01:03:21 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The strlcpy() function copies strings. It is designed to be safer, more
** consistent, and less error prone replacements for strncpy(3). Unlike this
** function, strlcpy() take the full size of the buffer (not just the length)
** and guarantee to NUL-terminate the result (as long as size is larger than 0).
** Note that a byte for the NUL should be included in size. Also note that
** strlcpy() only operate on true ``C'' strings. This means that for strlcpy()
** src must be NUL-terminated.
**
** The strlcpy() function copies up to size - 1 characters from the NUL-termina-
** ted string src to dst, NUL-terminating the result.
**
** The source and destination strings should not overlap, as the behavior is un-
** defined.
**
** RETURN VALUES
** The strlcpy() function returns the total length of the string they tried to
** create. For strlcpy() that means the length of src. While this may seem some-
** what confusing, it was done to make truncation detection simple.
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (i < size - 1)
		{
			dst[i] = src[i];
			if (dst[i] == '\0')
				break ;
			i++;
		}
		dst[i] = '\0';
	}
	i = 0;
	while (src[i] != '\0')
		i++;
	return (i);
}
