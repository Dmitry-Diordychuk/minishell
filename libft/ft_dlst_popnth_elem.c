/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_popnth_elem.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:48:14 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/18 16:41:03 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_delement	ft_dlst_popnth_elem(t_dlist **list, size_t n)
{
	size_t		size;
	t_delement	temp;

	size = ft_dlst_size(*list);
	if (list != NULL && *list != NULL && n < size)
	{
		if (n == 0)
			return (ft_dlst_popfirst_elem(list));
		temp = ft_dlst_getnth_elem(*list, n);
		ft_dlst_unlink_elem(temp);
		return (temp);
	}
	return (NULL);
}
