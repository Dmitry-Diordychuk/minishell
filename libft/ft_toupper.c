/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 01:50:29 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/10 01:24:01 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The toupper() function converts a lower-case letter to the corresponding
** upper-case letter. The argument must be representable as an unsigned char or
** the value of EOF.
**
** RETURN VALUES
** If the argument is a lower-case letter, the toupper() function returns the
** corresponding upper-case letter if there is one; other-wise, the argument is
** returned unchanged.
*/

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
