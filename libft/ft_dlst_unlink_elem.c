/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_unlink_elem.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 17:42:11 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/14 11:55:36 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlst_unlink_elem(t_delement elem)
{
	if (elem != NULL)
	{
		if (elem->prev == NULL && elem->next != NULL)
		{
			elem->next->prev = NULL;
			elem->next = NULL;
		}
		else if (elem->prev != NULL && elem->next == NULL)
		{
			elem->prev->next = NULL;
			elem->prev = NULL;
		}
		else if (elem->prev != NULL && elem->next != NULL)
		{
			elem->next->prev = elem->prev;
			elem->prev->next = elem->next;
			elem->prev = NULL;
			elem->next = NULL;
		}
	}
}
