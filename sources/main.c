/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:02:09 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/24 20:54:01 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_command_argument(char **input_line, int argc, char **argv)
{
	*input_line = NULL;
	if (!errno && argc > 1 && !ft_strcmp(argv[1], "-c"))
	{
		if (argc < 3)
		{
			msg("minishell: -c: option requires an argument", 0, 0);
			errno = EINVAL;
		}
		else
		{
			*input_line = argv[2];
			return (TRUE);
		}
	}
	if (errno)
		return (FALSE);
	return (FALSE);
}

int		run_command(t_data *data)
{
	data->wordlist = NULL;
	if (!errno)
		run_lexer(&data->wordlist, data->input_line);
	if (errno == EIO)
		msg("minishell: syntax error near unexpected token `newline'\n", 0, 0);
	if (errno == EIO)
		return (ERROR);
	while (data->wordlist != NULL)
	{
		data->table = NULL;
		if (run_parser(&data->wordlist, &data->table) ||
		run_expansion(&data->table, data->env))
		{
			errno = 0;
			break ;
		}
		if (execute(data->table, data->env))
			errno = 0;
		delete_cmdtbl(data->table);
		if (data->env->is_exit == TRUE)
			free(data->wordlist);
		if (data->env->is_exit == TRUE)
			break ;
	}
	return (errno ? ERROR : SUCCESSED);
}

int		run_loop(t_data *data)
{
	data->input_line = NULL;
	while (1)
	{
		set_signals(SIGMOD_SHELL);
		ft_putstr_fd("minishell: ", 1);
		if (readline(&data->input_line, &data->history, data->env))
			return (ERROR);
		if (data->env->is_exit == TRUE)
		{
			free(data->input_line);
			return (SUCCESSED);
		}
		if (!errno)
			run_command(data);
		free(data->input_line);
		data->input_line = NULL;
		if (data->env->is_exit == TRUE)
			return (SUCCESSED);
	}
	return (errno ? ERROR : SUCCESSED);
}

void	data_container(int set_get, t_data *ret_data)
{
	static t_data data;

	if (set_get == SET)
	{
		data = *ret_data;
	}
	else
	{
		*ret_data = data;
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_data	data;

	data_container(SET, &data);
	data.history = NULL;
	if (!(data.env = (t_env*)malloc(sizeof(t_env))))
		return (ERROR);
	if (init_env(envp, data.env))
		return (ERROR);
	if (check_command_argument(&(data.input_line), argc, argv))
		run_command(&data);
	else
		run_loop(&data);
	free_array(data.env->envs);
	free(data.env);
	ft_dlst_clear(&data.history, delete_record);
	return (data.env->last_return);
}
