/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 18:16:58 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/18 17:01:48 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Malloc with counter. Returns how much the ft_malloc() function has been
** called in ret_counter parametr. ret_counter can be NULL so that nothing will
** be return.
*/

void	*ft_malloc(size_t size, size_t *ret_counter)
{
	static size_t	counter;
	void			*result;

	if (!(result = malloc(size)))
	{
		if (ret_counter != NULL)
			*ret_counter = counter;
		return (NULL);
	}
	counter++;
	if (ret_counter != NULL)
		*ret_counter = counter;
	return (result);
}
