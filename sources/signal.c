/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:35:12 by ebarra            #+#    #+#             */
/*   Updated: 2021/03/25 20:37:42 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_signal_for_shell(int signal_code)
{
	t_data data;

	if (signal_code == SIGINT)
	{
		data_container(GET, &data);
		write(1, "\nminishell: ", 12);
		data.env->last_return = 0;
	}
	if (signal_code == SIGQUIT)
		data.env->last_return = 0;
}

static void	set_signal_for_wait(int signal_code)
{
	if (signal_code == SIGINT)
		;
	else if (signal_code == SIGQUIT)
		;
}

void		set_signals(int mode)
{
	if (mode == SIGMOD_WAIT)
	{
		signal(SIGINT, set_signal_for_wait);
		signal(SIGQUIT, set_signal_for_wait);
	}
	else if (mode == SIGMOD_SHELL)
	{
		signal(SIGINT, set_signal_for_shell);
		signal(SIGQUIT, set_signal_for_shell);
	}
	else if (mode == SIGMOD_DEFAULT)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
