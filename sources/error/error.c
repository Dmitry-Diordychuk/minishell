/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 05:28:29 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/24 23:26:58 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msg(char *mes1, char *mes2, char *mes3)
{
	if (mes1 != NULL)
		ft_putstr_fd(mes1, 2);
	if (mes1 != NULL)
		ft_putstr_fd(mes2, 2);
	if (mes1 != NULL)
		ft_putstr_fd(mes3, 2);
}

int		free_data(int ret)
{
	t_data data;

	data_container(GET, &data);
	free_array(data.env->envs);
	data.env->envs = NULL;
	delete_cmdtbl(data.table);
	data.table = NULL;
	ft_dlst_clear(&data.history, delete_record);
	ft_dlst_clear(&data.wordlist, delete_word_desc);
	free(data.input_line);
	data.input_line = NULL;
	return (ret);
}
