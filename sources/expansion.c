/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:13:50 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/24 21:20:18 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			set_buildin_flag(t_simcmd *simcmd, char *command_word)
{
	int		i;
	char	*lowercase_command_word;

	if (!(lowercase_command_word = ft_strdup(command_word)))
		errno = ENOMEM;
	i = -1;
	while (!errno && lowercase_command_word[++i] != '\0')
		lowercase_command_word[i] = ft_tolower(lowercase_command_word[i]);
	if (!errno && !ft_strcmp(lowercase_command_word, "echo"))
		simcmd->buildin = BUILD_ECHO;
	else if (!errno && !ft_strcmp(lowercase_command_word, "cd"))
		simcmd->buildin = BUILD_CD;
	else if (!errno && !ft_strcmp(lowercase_command_word, "pwd"))
		simcmd->buildin = BUILD_PWD;
	else if (!errno && !ft_strcmp(lowercase_command_word, "export"))
		simcmd->buildin = BUILD_EXPORT;
	else if (!errno && !ft_strcmp(lowercase_command_word, "unset"))
		simcmd->buildin = BUILD_UNSET;
	else if (!errno && !ft_strcmp(lowercase_command_word, "env"))
		simcmd->buildin = BUILD_ENV;
	else if (!errno && !ft_strcmp(lowercase_command_word, "exit"))
		simcmd->buildin = BUILD_EXIT;
	free(lowercase_command_word);
	return (1);
}

static int	error_handl(char **path, char **ret_name)
{
	errno = ENOENT;
	msg("minishell: ", *path, ": No such file or directory\n");
	free(path);
	free(*ret_name);
	return (ERROR);
}

int			init_redirection_field(char **ret_name, t_dlist **file_tokens,
								int io_type, t_env *env)
{
	char	*path;

	if (peek_word(*file_tokens) == FILE_SEPARATOR)
		ft_dlst_removefirst(file_tokens, delete_word_desc);
	if (*file_tokens == NULL)
		return (SUCCESSED);
	free(*ret_name);
	*ret_name = glue_words(file_tokens, env->envs, &env->last_return);
	if (!(path = getcwd(NULL, 0)))
	{
		free(*ret_name);
		return (ERROR);
	}
	if (io_type == (OPERATOR | LESS))
		if (!check_existence(path, *ret_name))
			return (error_handl(&path, ret_name));
	if ((extend_path(*ret_name, &path)))
		return (ERROR);
	free(*ret_name);
	*ret_name = path;
	if (!errno && (io_type == GREAT || io_type == GREATGREAT))
		if (create_file(path, O_RDWR | O_CREAT, 0644))
			return (ERROR);
	return (errno ? ERROR : SUCCESSED);
}

int			expand_redirection(t_cmdtbl **table, t_env *env)
{
	if (!errno)
		while ((*table)->in_file_list != NULL)
			if (init_redirection_field(&(*table)->in_file,
			&(*table)->in_file_list, LESS, env))
				return (ERROR);
	if (!errno)
		while ((*table)->out_file_list != NULL)
			if (init_redirection_field(&(*table)->out_file,
			&(*table)->out_file_list, GREAT, env))
				return (ERROR);
	return (SUCCESSED);
}

int			run_expansion(t_cmdtbl **table, t_env *env)
{
	t_diter		iter;
	t_simcmd	*sim;
	char		*tmp;

	ft_diter_init(&(*table)->rows, &iter);
	while (!errno && ft_diter_more(&iter))
	{
		if (!errno)
			sim = (t_simcmd*)ft_diter_getnext(&iter);
		if (!errno)
			tmp = glue_words(&sim->argv_list, (*env).envs, &(*env).last_return);
		if (!errno)
			set_buildin_flag(sim, tmp);
		if (!errno)
			add_arg(sim, tmp);
		while (!errno && sim->argv_list != NULL)
		{
			tmp = glue_words(&sim->argv_list, (*env).envs, &(*env).last_return);
			if (!errno)
				add_arg(sim, tmp);
		}
	}
	if (expand_redirection(table, env))
		return (ERROR);
	return (errno ? ERROR : SUCCESSED);
}
