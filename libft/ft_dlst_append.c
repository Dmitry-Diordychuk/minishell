/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:13:09 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/14 11:54:09 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlst_append(t_dlist **dlst, t_delement elem)
{
	t_dlist *temp;

	if (dlst != NULL && elem != NULL)
	{
		if (*dlst != NULL)
		{
			temp = *dlst;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = elem;
			elem->prev = temp;
		}
		else
			*dlst = elem;
	}
}
