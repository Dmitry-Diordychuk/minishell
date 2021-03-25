/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:55:42 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/25 16:08:38 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		extend_path(char *filename, char **path)
{
	char *tmp;

	if (!(tmp = ft_strjoin(*path, "/")))
	{
		errno = ENOMEM;
		*path = NULL;
		return (ALLOCATION_ERROR);
	}
	free(*path);
	if (!(*path = ft_strjoin(tmp, filename)))
	{
		errno = ENOMEM;
		*path = NULL;
		free(tmp);
		return (ALLOCATION_ERROR);
	}
	free(tmp);
	return (SUCCESSED);
}

t_bool	check_full_path(char *program_name)
{
	int		i;

	i = ft_strlen(program_name) - 1;
	while (i > 0 && program_name[i] != '/')
		i--;
	program_name[i] = '\0';
	if (check_existence(program_name, program_name + i + 1))
	{
		program_name[i] = '/';
		return (TRUE);
	}
	program_name[i] = '/';
	return (FALSE);
}

char	**splite_path(char **envp)
{
	char *value;
	char **paths;

	if (!(value = find_env_var(envp, "PATH")))
		return (NULL);
	if (!(paths = ft_split(value, ':')))
	{
		errno = ENOMEM;
		free(value);
		return (NULL);
	}
	free(value);
	return (paths);
}

char	*search_in_path(char *name, char **envp)
{
	t_bool	findflag;
	char	*full_name;
	char	**paths;
	int		i;

	full_name = NULL;
	findflag = FALSE;
	if (!(paths = splite_path(envp)))
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
		if (!findflag && check_existence(paths[i], name))
		{
			findflag = TRUE;
			if (extend_path(name, &paths[i]))
			{
				free_array(paths);
				return (NULL);
			}
			full_name = paths[i++];
		}
		else
			free(paths[i++]);
	free(paths);
	return (full_name);
}

t_bool	check_dir_path(char *path)
{
	struct stat	st;

	if (!stat(path, &st))
	{
		if (S_ISDIR(st.st_mode))
			return (FALSE);
	}
	else
		return (FALSE);
	return (TRUE);
}
