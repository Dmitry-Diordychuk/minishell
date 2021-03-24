/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 18:14:22 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/10 01:18:31 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The strrchr() function is identical to strchr(), except it locates the last
** occurrence of c.
**
** RETURN VALUES
** The function strrchr() returns a pointer to the located character, or NULL
** if the character does not appear in the string.
*/

char	*ft_strrchr(const char *s, int c)
{
	char	*result;
	char	*prev;

	if ((result = ft_strchr(s, c)) == NULL)
		return (NULL);
	if (result[0] == '\0' && c == 0)
		return (result);
	while (result != NULL)
	{
		prev = result;
		result = ft_strchr(result + 1, c);
	}
	return (prev);
}
