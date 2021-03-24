/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:09:22 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/24 22:07:43 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_dlst_insert(t_dlist **dlst, t_delement elem, int n)
{
	int		size;
	t_dlist	*temp;

	size = ft_dlst_size(*dlst);
	if (dlst != NULL && *dlst != NULL && elem != NULL && n >= 0 && n < size)
	{
		if (n == 0)
			ft_dlst_prepend(dlst, elem);
		else if (n == size - 1)
			ft_dlst_append(dlst, elem);
		else
		{
			temp = ft_dlst_getnth_elem(*dlst, n);
			elem->next = temp;
			elem->prev = temp->prev;
			temp->prev->next = elem;
			temp->prev = elem;
		}
		return (TRUE);
	}
	return (FALSE);
}
