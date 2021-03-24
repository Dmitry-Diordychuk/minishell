/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:00:34 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/09 04:10:36 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_delement	ft_dlst_new(const t_ddata data)
{
	t_delement new_elem;

	new_elem = NULL;
	if (data != NULL)
	{
		new_elem = (t_dlist*)malloc(sizeof(t_dlist));
		if (new_elem != NULL)
		{
			new_elem->content = data;
			new_elem->sorted = FALSE;
			new_elem->next = NULL;
			new_elem->prev = NULL;
		}
	}
	return (new_elem);
}
