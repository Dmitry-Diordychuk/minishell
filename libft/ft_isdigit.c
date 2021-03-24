/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 01:39:08 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/10 00:04:39 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The isdigit() function tests for a decimal digit character. This includes the
** folowing characters only: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'.
**
** RETURN VALUES
** The isdigit() function returns zero if the character tests false and return
** non-zero if the character tests true.
*/

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
