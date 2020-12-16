/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 01:42:15 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/10 00:00:24 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The isalnum() function tests for any character for which isalpha() or
** isdigit() is true. The value of the argument must be representable as an
** unsigned char or the value of EOF.
**
** RETURN VALUES
** The isalnum() function returns zero if the character tests false and returns
** non-zero if the character test true.
*/

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
