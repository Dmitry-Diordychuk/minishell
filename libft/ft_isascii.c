/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 01:45:16 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/10 00:02:10 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The isascii() function test for an ASCII character, which is any character
** between 0 and octal 0177 inclusive.
*/

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
