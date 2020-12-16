/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 16:17:55 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/11 16:39:43 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	The function ft_lstfind() return the address of the first link, whose data
**	is "equal" to the reference data.
*/

t_list	*ft_lstfind(t_list *list, void *data_ref, int (*cmp)())
{
	if (list != NULL)
	{
		while (list->next != NULL)
		{
			if (cmp(data_ref, list->content) == 0)
				return (list);
			list = list->next;
		}
		if (cmp(data_ref, list->content) == 0)
			return (list);
	}
	return (NULL);
}
