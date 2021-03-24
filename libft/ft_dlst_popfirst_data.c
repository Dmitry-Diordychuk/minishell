/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_popfirst_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:41:06 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/14 11:54:52 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ddata	ft_dlst_popfirst_data(t_dlist **list)
{
	t_dlist	*head;
	t_ddata	data;

	head = ft_dlst_popfirst_elem(list);
	if (head != NULL)
	{
		data = head->content;
		free(head);
		return (data);
	}
	return (NULL);
}
