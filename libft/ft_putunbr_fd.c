/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 14:06:52 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/15 16:40:24 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunbr_fd(unsigned int n, int fd)
{
	int					digits[10];
	int					i;
	unsigned int long	number;

	number = n;
	i = 0;
	if (!number)
		ft_putchar_fd('0', fd);
	while (number)
	{
		digits[i] = number % 10;
		number = number / 10;
		i++;
	}
	while (i-- > 0)
	{
		ft_putchar_fd(digits[i] + '0', fd);
	}
}
