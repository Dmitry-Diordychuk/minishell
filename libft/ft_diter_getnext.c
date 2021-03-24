/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_diter_getnext.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:58:37 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/15 12:34:40 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ddata	ft_diter_getnext(t_diter *iter)
{
	t_dlist *next;

	if (iter->list != NULL)
	{
		if (iter->cur == NULL && *iter->list == NULL)
		{
			return (NULL);
		}
		else if (iter->cur == NULL && *iter->list != NULL)
		{
			next = *iter->list;
			iter->cur = next;
			return (next->content);
		}
		else if (iter->cur != NULL && *iter->list != NULL)
		{
			next = iter->cur->next;
			if (iter->cur->next == NULL)
				*iter->list = NULL;
			iter->cur = iter->cur->next;
			return (next->content);
		}
	}
	return (NULL);
}
