/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 11:18:59 by kdustin           #+#    #+#             */
/*   Updated: 2021/01/06 17:01:36 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

t_cmd	*create_cmd()
{
	t_cmd	*new_cmd;

	if (!(new_cmd = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	new_cmd->sim_cmds = NULL;
	return (new_cmd);
}

int add_command(t_list **commands)
{
	t_list	*new_elem;
	t_cmd	*new_cmd;

	if (!(new_cmd = create_cmd()))
		return (ALLOCATION_FAILED);
	if (!(new_elem = ft_lstnew((void*)new_cmd)))
	{
		free(new_cmd);
		return (ALLOCATION_FAILED);
	}
	ft_lstpush(commands, new_elem);
	return (SUCCESSED);
}

void delete_command(void *content)
{
	t_cmd *cmd;

	cmd = (t_cmd*)content;
	ft_lstclear(&cmd->sim_cmds, delete_sim_command);
}

int		insert_sim_cmd(t_cmd *cmd, t_sim_cmd *sim_cmd)
{
	t_list *new_elem;

	if (!(new_elem = ft_lstnew((void*)sim_cmd)))
		return (-1);
	ft_lstpush(&cmd->sim_cmds, new_elem);
	return (0);
}

char *extend_path(char *filename, char *path)
{
	char *tmp;

	if (!(tmp = ft_strjoin(path, "/")))
		return (NULL);
	if (!(path = ft_strjoin(tmp, filename)))
	{
		free(tmp);
		return (NULL);
	}
	return (ft_strdup(path));
}

int execbuildin(int argc, char **argv, char **envs)
{
	if (!ft_strcmp(argv[0], "echo"))
	{
		ft_echo(argv);
		return (1);
	}
	else if (!ft_strcmp(argv[0], "cd"))
		return (1);
	else if (!ft_strcmp(argv[0], "pwd"))
	{
		ft_pwd(argv);
		return (1);
	}
	else if (!ft_strcmp(argv[0], "export"))
		return (1);
	else if (!ft_strcmp(argv[0], "unset"))
		return (1);
	else if (!ft_strcmp(argv[0], "env"))
	{
		ft_env();
		return (1);
	}
	else if (!ft_strcmp(argv[0], "exit"))
	{
		ft_exit(argv, argc);
		return (2);
	}
	return (0);
}

void execute_error(int execve_ret, char *name)
{
	DIR	*dir;

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	if((dir = opendir(name)) && ft_strchr(name, '/'))
	{
		ft_putstr_fd(": is a directory\n", 2);
		closedir(dir);
	}
	else if (errno == EACCES)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (errno == E2BIG)
		ft_putstr_fd(": Argument list too long\n", 2);
	else if (errno == EFAULT)
		ft_putstr_fd(": Bad address\n", 2);
	else if (errno == EIO)
		ft_putstr_fd(": Remote I/O error\n", 2);
	else if (errno == ELOOP)
		ft_putstr_fd(": Too many levels of symbolic links\n", 2);
	else if (errno == ENAMETOOLONG)
		ft_putstr_fd(": File name too long\n", 2);
	else if (errno == ENOENT && ft_strchr(name, '/'))
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (errno == ENOEXEC)
		ft_putstr_fd(": Exec format error\n", 2);
	else if (errno == ENOMEM)
		ft_putstr_fd(": Cannot allocate memory\n", 2);
	else if (errno == ENOTDIR)
		ft_putstr_fd(": Not a directory\n", 2);
	else if (errno == ETXTBSY)
		ft_putstr_fd(": Text file busy\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
}

int	execute_program(t_sim_cmd *sim)
{
	char	*paths;
	char	**split;
	int		i;
	char	*fullname;
	int		res;

	if (find_env_var(g_env_vars, "PATH", &paths) == ALLOCATION_FAILED)
		return (ALLOCATION_FAILED);
	if (!(split = ft_split(paths, ':')))
	{
		free(paths);
		return (ALLOCATION_FAILED);
	}
	free(paths);
	i = 0;
	while (split[i] != NULL)
	{
		if (!(fullname = extend_path(sim->argv[0], split[i])))
		{
			free_array(split);
			return(ALLOCATION_FAILED);
		}
		res = execve(fullname, sim->argv, g_env_vars);
		free(fullname);
		i++;
	}
	execute_error(res, sim->argv[0]);
	free_array(split);
	return (0);
}

int		execute(t_cmd *command)
{
	const int	tmpin = dup(0);
	const int	tmpout = dup(1);
	int			first_out_file;
	int			last_in_file;
	int			append;
	int			fdin;
	int			fdout;
	t_sim_cmd	*sim;
	char		*path;
	int			fdpipe[2];
	int			ex;
	char		buf[100];
	int			tmp_in;

	sim = (t_sim_cmd*)command->sim_cmds->content;
	first_out_file = 0;
	last_in_file = 0;
	append = 0;
	if (!ft_strcmp(sim->argv[0], "exit") && command->sim_cmds->next == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		exit(1);
	}
	while (command->sim_cmds != NULL)
	{
		sim = (t_sim_cmd*)command->sim_cmds->content;
		if (sim->in_file != NULL)
			last_in_file = open(extend_path(sim->in_file, getcwd(buf, 100)), O_CREAT | O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
		if (command->sim_cmds->next == NULL)
		{
			if (last_in_file > 0)
			{
				dup2(last_in_file, 0);
				close(last_in_file);
			}
			else
				dup2(tmp_in, 0);
			close(tmp_in);
			if (first_out_file > 0)
				fdout = first_out_file;
			else if (sim->out_file != NULL)
			{
				if (sim->is_append)
					fdout = open(extend_path(sim->out_file, getcwd(buf, 100)), O_APPEND | O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
				else
					fdout = open(extend_path(sim->out_file, getcwd(buf, 100)), O_CREAT | O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
			}
			else
				fdout = dup(tmpout);
			dup2(fdout, 1);
			close(fdout);
		}
		else
		{
			if (first_out_file == 0 && sim->out_file != NULL)
			{
				if (sim->is_append)
					first_out_file = open(extend_path(sim->out_file, getcwd(buf, 100)), O_APPEND | O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
				else
					first_out_file = open(extend_path(sim->out_file, getcwd(buf, 100)), O_CREAT | O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
			}
			pipe(fdpipe);
			fdin = fdpipe[0];
			fdout = fdpipe[1];
			dup2(tmp_in, 0);
			close(tmp_in);
			dup2(fdout, 1);
			close(fdout);
			tmp_in = fdin;
		}
		g_pid = fork();
		if (g_pid == 0)
		{
			if (execbuildin(sim->argc, sim->argv, g_env_vars))
			{
				;
			}
			else
			{
				if (!ft_strchr(sim->argv[0], '/'))
				{
					if ((ex = execute_program(sim)) < 0)
						exit(ALLOCATION_FAILED);
				}
				else
				{
					if (!(path = extend_path(sim->argv[0], getcwd(buf, 100))))
						exit(ALLOCATION_FAILED);
					execute_error(execve(path, sim->argv, g_env_vars), sim->argv[0]);
					free(path);
				}
			}
			exit(g_last_result);
		}
		command->sim_cmds = command->sim_cmds->next;
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	int status;
	if (waitpid(g_pid, &status, 0) == -1)
	{
		perror("waitpid failed\n");
		return -1;
	}
	if (WIFEXITED(status))
	{
		g_last_result = WEXITSTATUS(status);
	}
	int sig;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			ft_putstr_fd("TEST\n", 2);
		}
	}
	return (SUCCESSED);
}
