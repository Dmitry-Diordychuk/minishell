/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 05:23:04 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/20 20:58:30 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				buildin_echo(int argc, char **argv)
{
	int			i;
	int			crlf;

	i = 1;
	crlf = 0;
	if (argc > 1)
	{
		while (argv[i] && !(ft_strcmp(argv[i++], "-n")))
			crlf++;
		i = crlf + 1;
		while (argv[i])
		{
			write(1, argv[i], ft_strlen(argv[i]));
			i++;
			if (i < argc)
				write(1, " ", 1);
		}
		if (!crlf)
			write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
	return (SUCCESSED);
}
