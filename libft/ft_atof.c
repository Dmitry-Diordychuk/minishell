/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 02:24:45 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/14 11:53:46 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	atod(const char *str)
{
	double		num;
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
		num = (num * 10.0) + (*str - '0');
		str++;
	}
	return (num * minus);
}

static double	calc_expo(const char *str, double res)
{
	int		e;
	int		esign;

	e = 0;
	if (*str == 'e' || *str == 'E')
	{
		str++;
		esign = 1;
		if (*str == '-' && ft_isdigit(str[1]))
			esign = -1;
		e = atod(str) * esign;
	}
	while (e-- > 0)
	{
		if (esign == 1)
			res = res * 10;
		else
			res = res * 0.1;
	}
	return (res);
}

static int		is_nan_or_inf(const char *str)
{
	if (ft_strncmp("nan", str, 3) == 0 ||
		ft_strncmp("+nan", str, 4) == 0 ||
		ft_strncmp("-nan", str, 4) == 0 ||
		ft_strncmp("inf", str, 3) == 0 ||
		ft_strncmp("+inf", str, 4) == 0 ||
		ft_strncmp("-inf", str, 4) == 0)
		return (1);
	return (0);
}

static double	nan_or_inf(const char *str)
{
	if (ft_strncmp("-inf", str, 4) == 0)
		return (-1.0 / 0.0);
	else if (ft_strncmp("inf", str, 3) == 0 || ft_strncmp("+inf", str, 4) == 0)
		return (1.0 / 0.0);
	return (0.0 / 0.0);
}

double			ft_atof(const char *str)
{
	double	d;
	int		sign;
	double	res;

	while (ft_isspace(*str))
		str++;
	sign = (*str == '-' && ft_isdigit(str[1])) ? -1 : 1;
	if (is_nan_or_inf(str))
		return (nan_or_inf(str));
	res = atod(str) * sign;
	str = (*str == '+' || *str == '-') ? (str + 1) : str;
	while (ft_isdigit(*str))
		str++;
	if (*str == '.')
	{
		d = atod(++str);
		while (ft_isdigit(*str))
		{
			d = d / 10;
			str++;
		}
		res = calc_expo(str, res + d);
	}
	return (res * sign);
}
