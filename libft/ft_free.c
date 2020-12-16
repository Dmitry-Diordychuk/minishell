/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 18:33:02 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/18 17:09:28 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** free() function with counter. Returns how much calls of the ft_free() func-
** tion has been done.
*/

size_t	ft_free(void *ptr)
{
	static size_t	counter;

	free(ptr);
	counter++;
	return (counter);
}
