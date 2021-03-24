/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_between.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 23:55:06 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/14 00:45:09 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_between(const char *start, const char *end)
{
	size_t	len;
	char	*res;

	len = end - start + 1;
	if (!(res = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	ft_strlcpy(res, start, len);
	return (res);
}
