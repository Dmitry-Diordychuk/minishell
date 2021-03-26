/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 05:26:04 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/26 15:23:58 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					ft_strcmp_int(char *s1, char *s2)
{
	int				i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (i);
}

static char			**del_env(char *a, char **e, int len)
{
	char			**ne;
	int				i;
	int				k;
	int				y;

	i = -1;
	k = 0;
	if (!e || !(ne = (char **)malloc(sizeof(char *) * len)))
		return (NULL);
	while (e[++i])
	{
		y = ft_strcmp_int(e[i], a);
		if (!(ft_strncmp(e[i], a, y) == 0 && e[i][y] == '='))
		{
			if (!(ne[i - k] = ft_strdup(e[i])))
				return (ar_free(ne, i - k));
		}
		else
			k = 1;
	}
	ne[i - k] = 0;
	return (ne);
}

char				**buildin_unset2(char *argv, char **env, int len)
{
	int				i;
	int				j;
	int				del;
	char			**ne;

	i = 0;
	j = -1;
	del = 0;
	ne = env;
	while (env[++j])
	{
		i = ft_strcmp_int(env[j], argv);
		if (i && (env[j][i] == '='))
			del = 1;
	}
	if (del)
	{
		ne = del_env(argv, env, len);
		free_array(env);
	}
	return (ne);
}

int					buildin_unset(int argc, char **argv, t_data *env)
{
	int				i;
	int				len;

	i = 0;
	len = len_env(env->envs);
	if (argc > 1)
	{
		while (argv[++i])
		{
			env->envs = buildin_unset2(argv[i], env->envs, len);
		}
	}
	return (SUCCESSED);
}
