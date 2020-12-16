/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 21:13:26 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/18 17:07:33 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Takes as a parameter an element and frees the memory of the element’s content
** using the function’del’ given as a parameter and free the element. The memory
** of ’next’ must not be freed.
*/

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	t_list *temp;

	if (lst != NULL && del != NULL)
	{
		del(lst->content);
		temp = lst->next;
		ft_free(lst);
		lst = temp;
	}
}
