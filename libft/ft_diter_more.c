/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_diter_more.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:55:48 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/24 22:07:41 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_diter_more(t_diter *iter)
{
	if (iter->list != NULL)
	{
		if (iter->cur == NULL && *iter->list == NULL)
			return (FALSE);
		else if (iter->cur != NULL && iter->cur->next == NULL)
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}
