/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_poplast_elem.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:40:54 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/10 20:18:36 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_delement	ft_dlst_poplast_elem(t_dlist **list)
{
	t_dlist *temp;

	if (list != NULL && *list != NULL)
	{
		temp = *list;
		if (temp->next == NULL)
			*list = NULL;
		while (temp->next != NULL)
			temp = temp->next;
		ft_dlst_unlink_elem(temp);
		return (temp);
	}
	return (NULL);
}
