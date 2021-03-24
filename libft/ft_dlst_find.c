/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:20:19 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/14 11:54:21 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_delement	ft_dlst_find(t_dlist *list, t_dequlfunc equl, t_ddata data)
{
	if (list != NULL && equl != NULL && data != NULL)
	{
		while (list != NULL)
		{
			if (equl(list->content, data) == TRUE)
				return (list);
			list = list->next;
		}
	}
	return (NULL);
}
