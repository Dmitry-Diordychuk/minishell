/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 18:48:48 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/25 23:54:03 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		setup_fd(t_bool is_last, t_fd *fd, t_simcmd *simcmd)
{
	int	fdpipe[2];
	int	error;
	int	file_fd;

	error = 0;
	if (pipe(fdpipe))
		error = ERROR;
	if (simcmd->in_file)
	{
		close(fd->in);
		if ((file_fd = open(simcmd->in_file, O_RDONLY)) < 0)
		{
			msg(strerror(errno), "\n", 0);
			return (ERROR);
		}
		if (dup2(file_fd, 0) < 0 || close(file_fd) < 0)
			error = ERROR;
	}
	else
	{
		if (dup2(fd->in, 0) < 0 || close(fd->in) < 0)
			error = ERROR;
	}
	fd->in = fdpipe[0];
	if (simcmd->out_file)
	{
		if ((file_fd = open(simcmd->out_file, O_RDONLY)) < 0)
		{
			msg(strerror(errno), "\n", 0);
			return (ERROR);
		}
		if (dup2(file_fd, 1) < 0 || close(file_fd) < 0)
			error = ERROR;
		close(fdpipe[1]);
	}
	else if (is_last)
	{
		close(fdpipe[0]);
		close(fdpipe[1]);
		if (dup2(fd->tmpout, 1) < 0)
			error = ERROR;
	}
	else
	{
		fd->out = fdpipe[1];
		if (dup2(fd->out, 1) < 0 || close(fd->out) < 0)
			error = ERROR;
	}
	return (error == ERROR ? ERROR : SUCCESSED);
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
