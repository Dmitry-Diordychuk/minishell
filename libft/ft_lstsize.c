/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 20:21:24 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/10 00:26:26 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Counts the number of elements in a list.
**
** RETURN VALUE
** Length of the list.
*/

int	ft_lstsize(t_list *lst)
{
	int size;

	if (lst)
	{
		size = 0;
		while (lst->next != NULL)
		{
			lst = lst->next;
			size++;
		}
		return (++size);
	}
	return (0);
}
