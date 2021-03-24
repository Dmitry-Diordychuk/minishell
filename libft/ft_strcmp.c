/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 17:43:31 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/09 11:10:49 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The strcmp() function lexicographically compares the null-terminated strings
** s1 and s2.
**
** RETURN VALUES
** The ft_strcmp() function returns an integer greater than, equal to, or less
** than 0, according as the string s1 is greater than, equal to, or less than
** the string s2. The comparison is done using unsigned characters, so that
** `\200' is greater than `\0'.
*/

unsigned int	ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
