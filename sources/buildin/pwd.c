/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 05:26:01 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/20 21:00:03 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_declare_x(char *s1, char *s2)
{
	if (ft_strcmp(s1, "OLDPWD") == 0)
		write(1, "declare -x OLDPWD\n", 18);
	else
	{
		write(1, "declare -x ", 11);
		write(1, s1, ft_strlen(s1));
		write(1, "=\"", 2);
		write(1, s2, ft_strlen(s2));
		write(1, "\"\n", 2);
	}
}

char		**ar_free(char **ne, int size)
{
	int		i;
	char	**tmp;

	tmp = NULL;
	i = 0;
	while (size > i)
		free(ne[i++]);
	free(ne);
	return (tmp);
}

int			ft_strchr_int(char *s, int c)
{
	size_t	i;
	size_t	len;
	char	cc;

	i = 0;
	cc = (char)c;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == cc)
			return (i);
		i++;
	}
	return (0);
}

int			buildin_pwd(void)
{
	char	*buffer;
	char	buf[2048];

	buffer = getcwd(buf, sizeof(buf));
	write(1, buffer, ft_strlen(buffer));
	write(1, "\n", 1);
	return (SUCCESSED);
}
