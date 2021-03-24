/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_removelast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 13:10:00 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/24 22:07:46 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_dlst_removelast(t_dlist **list, t_ddelfunc del)
{
	t_delement elem;

	if (del != NULL)
	{
		elem = ft_dlst_poplast_elem(list);
		if (elem == NULL)
			return (FALSE);
		ft_dlst_del(elem, del);
		return (TRUE);
	}
	return (FALSE);
}
