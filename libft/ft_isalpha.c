/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 01:34:14 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/10 00:00:52 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The isalpha() function checks whether c is an alphabetic letter. The value of
** the argument must be represetable as an unsigned char or the value of EOF.
**
** RETURN VALUES
** The isalpha() function returns zero if the character tests false and returns
** non-zero if the character tests true.
*/

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
