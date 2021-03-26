/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 05:23:10 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/26 22:55:17 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			error_buildin_cd(char *a, char *s_oldpwd, char *s_pwd, int q)
{
	if (q == 1)
	{
		write(2, "minishell: cd: error", 20);
		free(s_oldpwd);
		free(s_pwd);
	}
	else
	{
		write(2, "minishell: cd: ", 15);
		write(2, a, ft_strlen(a));
		write(2, ": no such file or directory\n", 28);
		free(s_oldpwd);
		free(s_pwd);
	}
	return (1);
}

int			buildin_cd3(char *s_pwd, char *s_oldpwd, t_data *env)
{
	char	**ss;
	int		ret;

	if (!s_pwd || !s_oldpwd || !(ss = (char **)malloc(sizeof(char *) * 4)))
		return (error_buildin_cd(s_pwd, s_oldpwd, s_pwd, 1));
	ss[0] = ft_strdup("1");
	ss[1] = s_pwd;
	ss[2] = s_oldpwd;
	ss[3] = NULL;
	ret = buildin_export(3, ss, env);
	free(ss[2]);
	free(ss[1]);
	free(ss[0]);
	free(ss);
	return (ret);
}

int			buildin_cd2(char *a, char *s_oldpwd, t_data *env)
{
	int		ret;
	char	*buffer;
	char	buf[2048];
	char	*s_pwd;

	ret = chdir(a);
	buffer = getcwd(buf, sizeof(buf));
	s_pwd = ft_strjoin("PWD=", buffer);
	if (ret < 0)
		return (error_buildin_cd(a, s_oldpwd, s_pwd, 0));
	else
	{
		return (buildin_cd3(s_pwd, s_oldpwd, env));
	}
	return (0);
}

int			buildin_cd(int argc, char **argv, t_data *env)
{
	char	*home;
	char	*oldpwd;
	char	*s_oldpwd;

	if (argc == 1)
	{
		home = find_env_var(env->envs, "HOME");
		chdir(home);
		free(home);
	}
	else if (argc > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	else
	{
		oldpwd = find_env_var(env->envs, "PWD");
		s_oldpwd = ft_strjoin("OLDPWD=", oldpwd);
		free(oldpwd);
		return (buildin_cd2(argv[1], s_oldpwd, env));
	}
	return (SUCCESSED);
}
