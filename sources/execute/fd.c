/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 18:48:48 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/26 14:37:34 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		insert_file_fd(char *file_name, int mode, int insert_to_fd)
{
	int file_fd;

	if ((file_fd = open(file_name, mode)) < 0)
	{
		msg(strerror(errno), "\n", 0);
		return (ERROR);
	}
	if (dup2(file_fd, insert_to_fd) < 0 || close(file_fd) < 0)
		return (ERROR);
	return (SUCCESSED);
}

int		setup_out(t_bool is_last, t_fd *fd, t_simcmd *simcmd, int *fdpipe)
{
	int error;

	error = 0;
	if (simcmd->out_file)
	{
		if (simcmd->is_append)
			error = insert_file_fd(simcmd->out_file, O_WRONLY | O_APPEND, 1);
		else
			error = insert_file_fd(simcmd->out_file, O_WRONLY, 1);
		close(fdpipe[1]);
	}
	else if (is_last)
	{
		if (dup2(fd->tmpout, 1) < 0)
			error = ERROR;
	}
	else if ((fd->out = fdpipe[1]))
		if (dup2(fd->out, 1) < 0 || close(fd->out) < 0)
			error = ERROR;
	return (error ? error : SUCCESSED);
}

int		setup_fd(t_bool is_last, t_fd *fd, t_simcmd *simcmd)
{
	int	fdpipe[2];
	int	error;

	error = 0;
	if (!is_last && pipe(fdpipe))
		error = ERROR;
	if (simcmd->in_file)
	{
		close(fd->in);
		error = insert_file_fd(simcmd->in_file, O_RDONLY, 0);
	}
	else if (dup2(fd->in, 0) < 0 || close(fd->in) < 0)
		error = ERROR;
	fd->in = fdpipe[0];
	error = setup_out(is_last, fd, simcmd, fdpipe);
	return (error ? error : SUCCESSED);
}

int		restore_fd(t_fd *fd)
{
	if (
	dup2(fd->tmpin, 0) < 0 ||
	dup2(fd->tmpout, 1) < 0 ||
	close(fd->tmpout) < 0 ||
	close(fd->tmpin) < 0)
	{
		msg(strerror(errno), "\n", 0);
		return (ERROR);
	}
	return (SUCCESSED);
}

int		init_fd(t_fd *fd)
{
	if ((fd->tmpin = dup(0)) < 0 ||
	(fd->tmpout = dup(1)) < 0)
	{
		msg(strerror(errno), "\n", 0);
		return (ERROR);
	}
	else if ((fd->in = dup(fd->tmpin)) < 0)
	{
		msg(strerror(errno), "\n", 0);
		return (ERROR);
	}
	return (SUCCESSED);
}
