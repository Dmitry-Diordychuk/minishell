/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:02:09 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/26 20:50:19 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_command_argument(char **input_line, int argc, char **argv)
{
	*input_line = NULL;
	if (argc > 1 && !ft_strcmp(argv[1], "-c"))
	{
		if (argc < 3)
		{
			msg("minishell: -c: option requires an argument", 0, 0);
			return (FALSE);
		}
		else
		{
			*input_line = argv[2];
			return (TRUE);
		}
	}
	return (FALSE);
}

int		run_command(t_data *data)
{
	int error;

	data->wordlist = NULL;
	if ((error = run_lexer(&data->wordlist, data->input_line)))
		return (error);
	while (data->wordlist != NULL)
	{
		data->table = NULL;
		if ((error = run_parser(&(data->wordlist), &data->table)))
			return (error);
		if ((error = run_expansion(&data->table, data)))
			return (error);
		if ((error = execute(data->table, data)))
			return (error);
		delete_cmdtbl(data->table);
		if (data->is_exit == TRUE)
			free(data->wordlist);
		if (data->is_exit == TRUE)
			break ;
	}
	return (error ? error : SUCCESSED);
}

int		run_loop(t_data *data)
{
	int error;

	data->input_line = NULL;
	while (1)
	{
		set_signals(SIGMOD_SHELL);
		ft_putstr_fd("minishell: ", 1);
		if (readline(&data->input_line, &data->history, data))
			return (ERROR);
		if (data->is_exit == TRUE)
			free(data->input_line);
		if (data->is_exit == TRUE)
			return (SUCCESSED);
		error = run_command(data);
		if (error == ALLOCATION_ERROR)
			return (ALLOCATION_ERROR);
		else if (error == TOKEN_ERROR)
			data->last_return = 258;
		free(data->input_line);
		data->input_line = NULL;
		if (data->is_exit == TRUE)
			return (SUCCESSED);
	}
	return (SUCCESSED);
}

void	data_container(int set_get, t_data *ret_data)
{
	static t_data data;

	if (set_get == SET)
		data = *ret_data;
	else
		*ret_data = data;
}

int		main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		error;

	data_container(SET, &data);
	data.history = NULL;
	if (init_env(envp, &data))
		return (ERROR);
	data.envs =
			buildin_unset2("OLDPWD", data.envs, array_len(data.envs));
	if (check_command_argument(&(data.input_line), argc, argv))
		error = run_command(&data);
	else
		error = run_loop(&data);
	free_array(data.envs);
	ft_dlst_clear(&data.history, delete_record);
	if (error)
		return (error);
	return (data.last_return);
}
