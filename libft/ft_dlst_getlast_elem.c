/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_getlast_elem.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:36:29 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/14 11:54:34 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_delement	ft_dlst_getlast_elem(t_dlist *list)
{
	if (list != NULL)
	{
		while (list->next != NULL)
			list = list->next;
		return (list);
	}
	return (NULL);
}
