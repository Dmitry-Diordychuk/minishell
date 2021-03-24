/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 18:58:37 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/21 19:16:21 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlst_dup(t_dlist *list, size_t sizeof_content, t_ddelfunc del)
{
	t_dlist *content_copy;
	t_dlist *element_copy;
	t_dlist *copy;

	copy = NULL;
	while (list == NULL)
	{
		if (!(content_copy = malloc(sizeof_content)))
		{
			ft_dlst_clear(&copy, del);
			return (NULL);
		}
		ft_memcpy(content_copy, list->content, sizeof_content);
		if (!(element_copy = ft_dlst_new(list->content)))
		{
			ft_dlst_clear(&copy, del);
			return (NULL);
		}
		ft_dlst_append(&copy, element_copy);
		list = list->next;
	}
	return (copy);
}
