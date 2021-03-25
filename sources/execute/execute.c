/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 11:18:59 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/26 00:43:23 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		wait_after_fork(t_env *env, int ret)
{
	int		status;

	set_signals(SIGMOD_WAIT);
	if (waitpid(ret, &status, WNOHANG | WUNTRACED) == -1)
	{
		ft_putendl_fd(strerror(errno), 1);
		exit(free_data(1));
	}
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			env->last_return = 130;
		else if (WTERMSIG(status) == SIGQUIT)
		{
			write(1, "Quit: 3", 7);
			env->last_return = 131;
		}
		write(1, "T", 1);
	}
	else if (WIFEXITED(status))
		env->last_return = WEXITSTATUS(status);
	else
		return (ERROR);
	return (SUCCESSED);
}

int		execute_fork(char *filename, char **argv, t_env *env)
{
	int		ret;

	if ((ret = fork()) < 0)
		msg(strerror(errno), "\n", 0);
	else if (ret == 0)
	{
		set_signals(SIGMOD_DEFAULT);
		if (execve(filename, argv, env->envs) < 0)
			msg(strerror(errno), "\n", 0);
		exit(1);
	}
	else if (ret > 0)
		wait_after_fork(env, ret);
	free(filename);
	return (ret);
}

int		execute_buildin(t_simcmd *simcmd, t_env *env)
{
	int result;

	result = 0;
	if (simcmd->buildin == BUILD_ECHO)
		result = buildin_echo(simcmd->argc, simcmd->argv);
	else if (simcmd->buildin == BUILD_CD)
		result = buildin_cd(simcmd->argc, simcmd->argv, env);
	else if (simcmd->buildin == BUILD_PWD)
		result = buildin_pwd();
	else if (simcmd->buildin == BUILD_EXPORT)
		result = buildin_export(simcmd->argc, simcmd->argv, env);
	else if (simcmd->buildin == BUILD_UNSET)
		result = buildin_unset(simcmd->argc, simcmd->argv, env);
	else if (simcmd->buildin == BUILD_ENV)
		result = buildin_env(env);
	else if (simcmd->buildin == BUILD_EXIT)
	{
		env->is_exit = TRUE;
		result = buildin_exit(simcmd->argc, simcmd->argv, env);
	}
	return (result);
}

int		execute_simcmds(t_cmdtbl *table, t_env *env, t_fd *fd, int *pid)
{
	t_diter		iter;
	t_simcmd	*simcmd;
	char		*fullname;

	ft_diter_init(&table->rows, &iter);
	while (ft_diter_more(&iter) && (simcmd = ft_diter_getnext(&iter)))
	{
		if (setup_fd(!ft_diter_more(&iter), fd, simcmd))
			return (ERROR);
		*pid = 0;
		if (simcmd->buildin == EXTERNAL &&
		(fullname = find_program(simcmd->argv[0], env->envs)))
			*pid = execute_fork(fullname, simcmd->argv, env);
		else if (simcmd->buildin == EXTERNAL && (env->last_return = 127))
			continue ;
		else if (simcmd->buildin == BUILD_EXIT && ft_dlst_size(table->rows) > 1)
			continue ;
		else
			env->last_return = execute_buildin(simcmd, env);
	}
	return (SUCCESSED);
}

int		execute(t_cmdtbl *table, t_env *env)
{
	t_fd	fd;
	int		pid;
	int		error;

	pid = 0;
	if (init_fd(&fd))
	{
		msg(strerror(errno), "\n", 0);
		return (ERROR);
	}
	error = execute_simcmds(table, env, &fd, &pid);
	restore_fd(&fd);
	if (error)
		return (ERROR);
	return (SUCCESSED);
}
