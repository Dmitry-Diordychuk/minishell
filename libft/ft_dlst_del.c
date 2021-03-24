/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:05:52 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/14 11:54:17 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlst_del(t_delement elem, t_ddelfunc del)
{
	if (elem != NULL && del != NULL)
	{
		del((elem)->content);
		free(elem);
	}
}
