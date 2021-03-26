/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:13:50 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/26 15:36:57 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			set_buildin_flag(t_simcmd *simcmd, char *command_word)
{
	int		i;
	char	*lowercase_command_word;

	if (!(lowercase_command_word = ft_strdup(command_word)))
		return (ALLOCATION_ERROR);
	i = -1;
	while (lowercase_command_word[++i] != '\0')
		lowercase_command_word[i] = ft_tolower(lowercase_command_word[i]);
	if (!ft_strcmp(lowercase_command_word, "echo"))
		simcmd->buildin = BUILD_ECHO;
	else if (!ft_strcmp(lowercase_command_word, "cd"))
		simcmd->buildin = BUILD_CD;
	else if (!ft_strcmp(lowercase_command_word, "pwd"))
		simcmd->buildin = BUILD_PWD;
	else if (!ft_strcmp(lowercase_command_word, "export"))
		simcmd->buildin = BUILD_EXPORT;
	else if (!ft_strcmp(lowercase_command_word, "unset"))
		simcmd->buildin = BUILD_UNSET;
	else if (!ft_strcmp(lowercase_command_word, "env"))
		simcmd->buildin = BUILD_ENV;
	else if (!ft_strcmp(lowercase_command_word, "exit"))
		simcmd->buildin = BUILD_EXIT;
	free(lowercase_command_word);
	return (SUCCESSED);
}

static int	init_redirection_error(char **path, char **ret_name, int error)
{
	if (error < 0)
	{
		if (errno == ENOMEM)
			error = ALLOCATION_ERROR;
		else
		{
			msg(strerror(error), "\n", 0);
			error = ERROR;
		}
	}
	else if (error == 1)
		msg("minishell: ", *path, ": No such file or directory\n");
	free(path);
	free(*ret_name);
	return (ERROR);
}

int			init_redirection_field(char **ret_name, t_dlist **file_tokens,
								int io_type, t_data *env)
{
	char	*path;
	int		error;

	if (peek_word(*file_tokens) == FILE_SEPARATOR)
		ft_dlst_removefirst(file_tokens, delete_word_desc);
	if (*file_tokens == NULL)
		return (SUCCESSED);
	free(*ret_name);
	*ret_name = glue_words(file_tokens, env->envs, &env->last_return);
	if (!(path = getcwd(NULL, 0)))
		return (init_redirection_error(&path, ret_name, ERROR));
	if (io_type == (OPERATOR | LESS))
		if (!(error = check_existence(path, *ret_name)))
			return (init_redirection_error(&path, ret_name, error));
	if ((extend_path(*ret_name, &path)))
		return (init_redirection_error(&path, ret_name, ERROR));
	free(*ret_name);
	*ret_name = path;
	if (io_type == GREAT || io_type == GREATGREAT)
		if (create_file(path, O_RDWR | O_CREAT, 0644))
			return (ERROR);
	return (SUCCESSED);
}

int			expand_redirection(t_cmdtbl **table, t_data *env)
{
	int			error;
	t_diter		iter;
	t_simcmd	*simcmd;

	error = 0;
	ft_diter_init(&(*table)->rows, &iter);
	while (!error && ft_diter_more(&iter))
	{
		simcmd = ft_diter_getnext(&iter);
		while (simcmd->in_file_list != NULL)
			if ((error = init_redirection_field(&simcmd->in_file,
			&simcmd->in_file_list, LESS, env)))
				return (error);
		while (simcmd->out_file_list != NULL)
			if ((error = init_redirection_field(&simcmd->out_file,
			&simcmd->out_file_list, GREAT, env)))
				return (error);
	}
	return (SUCCESSED);
}

int			run_expansion(t_cmdtbl **table, t_data *e)
{
	t_diter		iter;
	t_simcmd	*s;
	char		*t;
	int			error;

	error = 0;
	ft_diter_init(&(*table)->rows, &iter);
	while (!error && ft_diter_more(&iter))
	{
		s = (t_simcmd*)ft_diter_getnext(&iter);
		if (!(t = glue_words(&s->argv_list, (*e).envs, &(*e).last_return)))
			error = ALLOCATION_ERROR;
		if (!error)
			error = set_buildin_flag(s, t);
		error = error ? error : add_arg(s, t);
		while (!error && s->argv_list != NULL)
		{
			if (!(t = glue_words(&s->argv_list, (*e).envs, &(*e).last_return)))
				error = ALLOCATION_ERROR;
			if (!error)
				error = add_arg(s, t);
		}
	}
	error = error ? error : expand_redirection(table, e);
	return (error ? error : SUCCESSED);
}
