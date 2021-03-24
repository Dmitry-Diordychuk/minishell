/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_popfirst_elem.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:36:04 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/14 11:54:57 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_delement	ft_dlst_popfirst_elem(t_dlist **list)
{
	t_dlist	*head;

	if (list != NULL && *list != NULL)
	{
		head = *list;
		*list = (*list)->next;
		ft_dlst_unlink_elem(head);
		return (head);
	}
	return (NULL);
}
