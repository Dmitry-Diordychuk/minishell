/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 01:05:45 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/10 10:53:18 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The atoi() function converts the initial portion of the string pointed to by
** str to int representation.
*/

int	ft_atoi(const char *str)
{
	long int	num;
	int			minus;

	minus = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		minus = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	num = 0;
	while (*str != '\0' && ft_isdigit(*str))
	{
		num += *str - '0';
		num *= 10;
		str++;
	}
	return (num / 10 * minus);
}
