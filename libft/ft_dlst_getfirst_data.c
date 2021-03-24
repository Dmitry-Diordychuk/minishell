/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_getfirst_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:31:37 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/14 11:54:24 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ddata	ft_dlst_getfirst_data(t_dlist *list)
{
	if (list != NULL)
		return (list->content);
	return (NULL);
}
