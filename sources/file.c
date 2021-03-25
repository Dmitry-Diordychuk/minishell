/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 10:14:45 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/25 16:11:01 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	check_existence(char *path, char *filename)
{
	DIR				*dirp;
	struct dirent	*dp;

	if (!(dirp = opendir(path)))
	{
		if (errno == ENOENT)
			return (FALSE);
		return (ERROR);
	}
	while ((dp = readdir(dirp)))
	{
		if (dp->d_namlen == ft_strlen(filename) &&
		!ft_strcmp(dp->d_name, filename))
		{
			closedir(dirp);
			return (TRUE);
		}
	}
	closedir(dirp);
	return (FALSE);
}

int		create_file(char *file, int mode, int chmod)
{
	int fd;

	if ((fd = open(file, mode, chmod)) < 0)
	{
		msg(strerror(errno), "\n", 0);
		return (ERROR);
	}
	close(fd);
	return (SUCCESSED);
}

char	*find_program(char *program_name, char **envp)
{
	char *full_path;

	if (ft_strchr(program_name, '/'))
	{
		if (!check_dir_path(program_name))
		{
			msg("minishell ", program_name, ": is a directory\n");
			return (NULL);
		}
		if (!check_full_path(program_name))
		{
			msg("minishell: no such file or directory: ", program_name, "\n");
			return (NULL);
		}
		full_path = ft_strdup(program_name);
	}
	else if (!(full_path = search_in_path(program_name, envp)))
	{
		msg("minishell: ", program_name, ": command not found\n");
		return (NULL);
	}
	return (full_path);
}
