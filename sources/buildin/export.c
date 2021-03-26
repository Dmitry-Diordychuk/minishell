/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 05:25:55 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/26 20:50:56 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		len_env(char **env)
{
	int			len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

char	**add_env(char *a, char **e, int len)
{
	char		**ne;
	int			i;

	i = -1;
	if (!e || !(ne = (char **)malloc(sizeof(char *) * (len + 2))))
		return (NULL);
	while (e[++i])
	{
		if (!(ne[i] = ft_strdup(e[i])))
			return (ar_free(ne, i + 1));
	}
	if (!(ne[i++] = ft_strdup(a)))
		return (ar_free(ne, len));
	ne[i] = 0;
	return (ne);
}

char	**change_env(char *a, char **e, int z, int len)
{
	char		**ne;
	int			i;

	i = -1;
	if (!e || !(ne = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (e[++i])
	{
		if (!ft_strncmp(e[i], a, z) && e[i][z] == '=')
		{
			if (!(ne[i] = ft_strdup(a)))
				return (ar_free(ne, len));
		}
		else
		{
			if (!(ne[i] = ft_strdup(e[i])))
				return (ar_free(ne, len));
		}
	}
	ne[i] = 0;
	return (ne);
}

char	**buildin_export2(char *argv, char **env, int z)
{
	const int	len = len_env(env);
	int			j;
	int			add;
	char		**ne;

	j = -1;
	add = 1;
	ne = env;
	while (env[++j])
	{
		if (!ft_strncmp(env[j], argv, z) && (env[j][z] == '='))
		{
			ne = change_env(argv, env, z, len);
			ar_free(env, len_env(env));
			add = 0;
			break ;
		}
	}
	if (z && add)
	{
		ne = add_env(argv, env, len);
		ar_free(env, len_env(env));
	}
	return (ne);
}

int		buildin_export(int argc, char **argv, t_data *env)
{
	int			i;
	int			z;
	char		*s;

	i = 0;
	z = 0;
	if (argc > 1)
	{
		while (argv[++i])
		{
			z = ft_strchr_int(argv[i], '=');
			if (z)
				env->envs = buildin_export2(argv[i], env->envs, z);
		}
	}
	else
	{
		if (!(s = ft_strdup("OLDPWD=")))
			return (ERROR);
		env->envs = buildin_export2(s, env->envs, 6);
		export_sort_print(env->envs);
		env->envs = buildin_unset2(s, env->envs, 6);
		free(s);
	}
	return (SUCCESSED);
}
