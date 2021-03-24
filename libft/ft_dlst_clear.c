/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:08:34 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/14 11:54:13 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlst_clear(t_dlist **dlst, t_ddelfunc del)
{
	t_dlist *temp;

	if (dlst != NULL && *dlst != NULL)
	{
		while (*dlst != NULL)
		{
			temp = (*dlst)->next;
			ft_dlst_del(*dlst, del);
			*dlst = temp;
		}
		*dlst = NULL;
	}
}
