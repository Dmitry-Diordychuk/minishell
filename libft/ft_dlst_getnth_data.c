/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_getnth_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 17:30:06 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/14 11:54:37 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ddata	ft_dlst_getnth_data(t_dlist *list, size_t n)
{
	t_delement elem;

	elem = ft_dlst_getnth_elem(list, n);
	if (elem != NULL)
		return (elem->content);
	return (NULL);
}
