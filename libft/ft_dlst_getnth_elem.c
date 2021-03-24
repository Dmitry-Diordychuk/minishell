/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_getnth_elem.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 17:36:22 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/18 16:41:23 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_delement	ft_dlst_getnth_elem(t_dlist *list, size_t n)
{
	size_t	i;
	size_t	size;

	size = ft_dlst_size(list);
	if (list != NULL && n < size)
	{
		i = 0;
		while (i < n)
		{
			list = list->next;
			i++;
		}
		return (list);
	}
	return (NULL);
}
