/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_poplast_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:44:08 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/14 11:55:00 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ddata	ft_dlst_poplast_data(t_dlist **list)
{
	t_delement	tail;
	t_ddata		data;

	tail = ft_dlst_poplast_elem(list);
	if (tail != NULL)
	{
		data = tail->content;
		free(tail);
		return (data);
	}
	return (NULL);
}
