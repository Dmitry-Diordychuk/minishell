/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 01:20:24 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/29 21:42:22 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Deletes and frees the given element and every successor of that element,
** using the function ’del’and free(3). Finally, the pointer to the list must be
** set to NULL.
*/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (lst != NULL)
	{
		while (*lst != NULL && del != NULL)
		{
			temp = (*lst)->next;
			del((*lst)->content);
			ft_free(*lst);
			(*lst) = temp;
		}
	}
}
