/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 20:12:04 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/11 18:58:49 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates (with malloc(3)) and returns a new element. The variable ’content’
** is initialized with the value of the parameter ’content’. The variable ’next’
** is initialized to NULL.
**
** RETURN VALUE
** The new element if it was allocated and NULL otherwise.
*/

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list*)ft_malloc(sizeof(t_list), NULL);
	if (new_node)
	{
		new_node->next = NULL;
		new_node->content = content;
	}
	return (new_node);
}
