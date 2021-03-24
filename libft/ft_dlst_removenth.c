/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_removenth.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 13:10:53 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/24 22:07:50 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_dlst_removenth(t_dlist **list, t_ddelfunc del, size_t n)
{
	t_delement elem;

	if (del != NULL)
	{
		if (n == 0)
			return (ft_dlst_removefirst(list, del));
		elem = ft_dlst_popnth_elem(list, n);
		if (elem == NULL)
			return (FALSE);
		ft_dlst_del(elem, del);
		return (TRUE);
	}
	return (FALSE);
}
