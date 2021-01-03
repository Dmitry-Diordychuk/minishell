/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 11:18:59 by kdustin           #+#    #+#             */
/*   Updated: 2021/01/03 23:42:43 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (1);
	else if (!ft_strcmp(argv[0], "cd"))
		return (1);
	else if (!ft_strcmp(argv[0], "pwd"))
		return (1);
	else if (!ft_strcmp(argv[0], "export"))
		return (1);
	else if (!ft_strcmp(argv[0], "unset"))
		return (1);
	else if (!ft_strcmp(argv[0], "env"))
		return (1);
	else if (!ft_strcmp(argv[0], "exit"))
		return (1);
	return (0);
}

int	execute_related(t_sim_cmd *sim)
{
	char	*paths;
	char	**split;
	int		i;
	char	*fullpath;

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
		if (!(fullpath = extend_path(sim->argv[0], split[i])))
		{
			free_array(split);
			return(ALLOCATION_FAILED);
		}
		if (execve(fullpath, sim->argv, g_env_vars) >= 0)
		{
			free_array(split);
			free(fullpath);
			return (1);
		}
		free(fullpath);
		i++;
	}
	free_array(split);
	return (0);
}

int		execute(t_cmd *command)
{
	const int	tmpin = dup(0);
	const int	tmpout = dup(1);
	int			fdin;
	int			fdout;
	pid_t		pid;
	t_sim_cmd	*sim;
	char		*path;
	int			fdpipe[2];
	int			ex;
	char		buf[100];

	while (command->sim_cmds != NULL)
	{
		sim = (t_sim_cmd*)command->sim_cmds->content;
		if (sim->in_file)
			fdin = open(sim->in_file, O_RDONLY);
		else
			fdin = dup(tmpin);
		if (command->sim_cmds->next == NULL)
		{
			if (sim->out_file)
				fdout = open(sim->out_file, O_RDWR);
			else
				fdout = dup(tmpout);
		}
		else
		{
			pipe(fdpipe);
			fdin = fdpipe[0];
			fdout = fdpipe[1];
		}
		dup2(fdin, 0);
		close(fdin);
		dup2(fdout, 1);
		close(fdout);

		pid = fork();
		if (pid == 0)
		{

			if (execbuildin(sim->argc, sim->argv, g_env_vars))
				;
			else
			{
				if (!ft_strchr(sim->argv[0], '/'))
				{
					if ((ex = execute_related(sim)) < 0)
						exit(ALLOCATION_FAILED);
				}
				else if (*(sim->argv[0]) == '.')
				{
					if (!(path = extend_path(sim->argv[0], getcwd(buf, 100))))
						exit(ALLOCATION_FAILED);
					execve(path, sim->argv, g_env_vars);
					free(path);
				}
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(sim->argv[0], 2);
				ft_putstr_fd(": command not found\n", 2);
			}
			exit(1);
		}
		dup2(tmpin, 0);
		dup2(tmpout, 1);
		waitpid(pid, NULL, WUNTRACED);
		command->sim_cmds = command->sim_cmds->next;
	}
	close(tmpin);
	close(tmpout);
	return (SUCCESSED);
}
