/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_prepend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:20:06 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/14 11:55:14 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlst_prepend(t_dlist **dlst, t_delement elem)
{
	if (dlst != NULL && elem != NULL)
	{
		if (*dlst != NULL)
		{
			elem->next = *dlst;
			(*dlst)->prev = elem;
			(*dlst) = elem;
		}
		else
			*dlst = elem;
	}
}
