/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 01:58:36 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/10 01:22:54 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The tolower() function converts an upper-case letter to the corresponding
** lower-case letter. The argument must be representable as an unsigned char or
** the value of EOF.
**
** RETURN VALUES
** If the argument is an upper-case letter, the tolower() function returns the
** corresponding lower-case letter if there is one; other-wise, the argument is
** returned unchanged.
*/

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
