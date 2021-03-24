/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_diter_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:26:45 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/15 12:34:45 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_diter_remove(t_diter *iter, t_ddelfunc del)
{
	t_dlist *temp;

	if (iter->list != NULL)
	{
		if (iter->cur != NULL)
		{
			if (iter->cur->prev == NULL)
			{
				*iter->list = iter->cur->next;
				ft_dlst_unlink_elem(iter->cur);
				ft_dlst_del(iter->cur, del);
				iter->cur = NULL;
			}
			else
			{
				temp = iter->cur->prev;
				ft_dlst_unlink_elem(iter->cur);
				ft_dlst_del(iter->cur, del);
				iter->cur = temp;
			}
		}
	}
}
