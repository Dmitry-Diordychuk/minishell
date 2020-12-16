/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:09:34 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/20 14:14:34 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	The function ft_strrotate() rotates the order of the chars in c type string.
**	RETURN VALUE
**	It's return rotated string.
*/

char	*ft_strrotate(char *str)
{
	size_t	i;
	size_t	j;
	size_t	len_half;

	i = 0;
	j = ft_strlen(str) - 1;
	len_half = (j / 2) + 1;
	while (i < len_half)
	{
		str[i + j + 1] = str[i];
		str[i] = str[j];
		str[j] = str[i + j + 1];
		i++;
		j--;
	}
	str[i + j + 1] = '\0';
	return (str);
}
