/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 05:25:47 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/24 21:03:20 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_atoi_exit(const char *nptr, int *e)
{
	unsigned long long	res;
	int					sign;

	res = 0;
	sign = 1;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr && *nptr == '0')
		nptr++;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - 48);
		nptr++;
		(*e)++;
	}
	if (*nptr && !(*nptr >= '0' && *nptr <= '9') && (*e = 0))
		return (0);
	if (res > 9223372036854775807 || *e > 20)
		*e = 0;
	return ((int)res * sign);
}

int			buildin_exit_error(char *arvg)
{
	write(1, "minishell: exit: ", 17);
	write(1, arvg, ft_strlen(arvg));
	write(1, ": numeric argument required\n", 28);
	return (2);
}

int			buildin_exit3(int i)
{
	while (i < 0)
		i = i + 256;
	while (i > 255)
		i = i - 256;
	return (i);
}

int			buildin_exit2(int argc, t_env *env, int ii)
{
	if (argc > 2)
	{
		write(1, "minishell: exit: too many arguments\n", 36);
		env->is_exit = FALSE;
		return (1);
	}
	else
		return (buildin_exit3(ii));
	return (0);
}

int			buildin_exit(int argc, char **argv, t_env *env)
{
	int					ii;
	char				*s;
	int					e;

	write(1, "exit\n", 5);
	if (argc < 2)
		return (buildin_exit3(env->last_return));
	else
	{
		e = 1;
		s = ft_strtrim(argv[1], " \t\n\v\f\r");
		ii = ft_atoi_exit(s, &e);
		free(s);
		if (e == 0)
			return (buildin_exit_error(argv[1]));
		else
			return (buildin_exit2(argc, env, ii));
	}
	return (env->last_return);
}
