/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_popnth_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:47:51 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/14 11:55:07 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ddata	ft_dlst_popnth_data(t_dlist **list, size_t n)
{
	t_delement	nth;
	t_ddata		data;

	nth = ft_dlst_popnth_elem(list, n);
	if (nth != NULL)
	{
		data = nth->content;
		free(nth);
		return (data);
	}
	return (NULL);
}
