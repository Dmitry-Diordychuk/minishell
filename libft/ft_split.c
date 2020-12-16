/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:49:12 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/18 17:07:35 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates (with malloc(3)) and returns an array of strings obtained by split-
** ting ’s’ using the character ’c’ as a delimiter. The array must be ended by a
** NULL pointer.
**
** RETURN VALUE
** The array of new strings resulting from the split. NULL if the allocation
** fails.
*/

int		get_malloc_len(char const *s, char c)
{
	size_t	i;
	int		counter;

	if (s == NULL)
		return (0);
	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			counter++;
		}
		if (s[i] != '\0')
			i++;
	}
	return (counter);
}

char	**fill_array(char **array, char const *s, char c)
{
	const char	*start;
	const char	*end;
	size_t		i;

	start = s;
	end = s;
	i = 0;
	while (*start != '\0')
	{
		while (*start == c)
			start++;
		if (*start == '\0')
			break ;
		end = start;
		while (*end != '\0' && *end != c)
			end++;
		if (!(array[i] = ft_calloc(end - start + 1, sizeof(char))))
			return (NULL);
		ft_strlcpy(array[i], start, end - start + 1);
		i++;
		start = end;
	}
	return (array);
}

void	free_result(char **array, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		ft_free(array[i]);
	}
	ft_free(array);
}

char	**ft_split(char const *s, char c)
{
	char			**result;
	const size_t	len = get_malloc_len(s, c) + 1;

	if (s == NULL)
		return (NULL);
	if (!(result = (char**)ft_calloc(len, sizeof(char*))))
		return (NULL);
	if (!(result = fill_array(result, s, c)))
	{
		free_result(result, len);
		return (NULL);
	}
	return (result);
}
