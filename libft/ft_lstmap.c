/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 14:41:31 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/11 16:11:18 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** XXX
** Iterates the list ’lst’ and applies the function’f’ to the content of each
** element. Creates a newlist resulting of the successive applications of the
** function ’f’. The ’del’ function is used to delete the content of an element
** if needed.
**
** RETURN VALUE
** The new list. NULL if the allocation fails.
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	**head;
	t_list	*new_list;
	t_list	*new_element;

	new_list = NULL;
	head = &new_list;
	if (lst != NULL && f != NULL)
	{
		if (!(new_list = ft_lstnew(f(lst->content))))
			return (NULL);
		lst = lst->next;
		while (lst != NULL)
		{
			new_element = ft_lstnew(f(lst->content));
			ft_lstadd_back(&new_list, new_element);
			if (new_element == NULL)
			{
				if (del != NULL)
					ft_lstclear(head, del);
				return (NULL);
			}
			lst = lst->next;
		}
	}
	return (new_list);
}
