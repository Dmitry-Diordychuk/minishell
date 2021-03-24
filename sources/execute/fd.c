/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 18:48:48 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/24 23:25:28 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		setup_fd(t_bool is_last, t_fd *fd, char *out_file, int is_append)
{
	int	fdpipe[2];
	int	error;

	error = 0;
	if (dup2(fd->in, 0) < 0 || close(fd->in) < 0)
		error = ERROR;
	if (is_last && out_file && !is_append)
		if ((fd->out = open(out_file, O_WRONLY)) < 0)
			error = ERROR;
	if (is_last && out_file && is_append)
		if ((fd->out = open(out_file, O_WRONLY | O_APPEND)) < 0)
			error = ERROR;
	if (is_last && !out_file)
		if ((fd->out = dup(fd->tmpout)) < 0)
			error = ERROR;
	if (!is_last)
	{
		if (pipe(fdpipe))
			error = ERROR;
		fd->out = fdpipe[1];
		fd->in = fdpipe[0];
	}
	if (dup2(fd->out, 1) < 0 || close(fd->out) < 0)
		error = ERROR;
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

int		init_fd(t_fd *fd, char *in_file)
{
	if ((fd->tmpin = dup(0)) < 0 ||
	(fd->tmpout = dup(1)) < 0)
	{
		msg(strerror(errno), "\n", 0);
		return (ERROR);
	}
	if (in_file)
	{
		if ((fd->in = open(in_file, O_RDONLY)) < 0)
		{
			msg(strerror(errno), "\n", 0);
			return (ERROR);
		}
	}
	else if ((fd->in = dup(fd->tmpin)) < 0)
	{
		msg(strerror(errno), "\n", 0);
		return (ERROR);
	}
	return (SUCCESSED);
}
