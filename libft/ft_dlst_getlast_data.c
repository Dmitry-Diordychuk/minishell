/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_getlast_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:33:48 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/14 11:54:31 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ddata	ft_dlst_getlast_data(t_dlist *list)
{
	if (list != NULL)
	{
		while (list->next != NULL)
			list = list->next;
		return (list->content);
	}
	return (NULL);
}
