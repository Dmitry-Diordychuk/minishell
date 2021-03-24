/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 01:48:25 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/10 00:06:22 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The isprint() function checks whether c is a printable character.
**
** RETURN VALUES
** The isprint() function returns zero if the character tests false and returns
** non-zero if the character tests true.
*/

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
