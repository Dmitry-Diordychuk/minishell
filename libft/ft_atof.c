/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 02:24:45 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 02:25:02 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(char *str)
{
	int		n;
	double	d;
	int		len;
	int		sign;

	sign = 1;
	if (str[0] == '-' && str[1] == '0')
		sign = -1;
	d = 0;
	len = 0;
	n = ft_atoi(str);
	while (ft_isdigit(*str) || *str == '-')
		str++;
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(str[len]))
			len++;
		d = ft_atoi(str);
	}
	while (len-- > 0)
		d = d / 10;
	if (n < 0)
		d = d * -1;
	return (((double)n + d) * sign);
}
