/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 17:45:26 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/26 16:37:14 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	signal_c_key(t_dlist **cur_record, t_dlist **history, int *cur_pos,
																t_data *data)
{
	if (apply_func(history, reset_str))
		return (ALLOCATION_ERROR);
	ft_dlst_removefirst(history, delete_record);
	if (tputs(tgetstr("do", 0), 1, ft_putchar))
		return (ERROR);
	if (apply_func(history, save_str))
		return (ALLOCATION_ERROR);
	if (add_record(history, ""))
		return (ALLOCATION_ERROR);
	*cur_record = *history;
	if (tputs(tgetstr("ks", 0), 1, ft_putchar))
		return (ERROR);
	if (tputs(tgetstr("sc", 0), 1, ft_putchar))
		return (ERROR);
	*cur_pos = 0;
	if (tputs(tgetstr("dl", 0), 1, ft_putchar))
		return (ERROR);
	ft_putstr_fd("minishell: ", 1);
	data->last_return = 1;
	return (SUCCESSED);
}

int	special_keys(t_dlist **cur_record, int *cur_pos)
{
	char		buf[4];
	int			error;

	error = 0;
	buf[0] = '\e';
	read(0, buf + 1, 2);
	buf[3] = '\0';
	if (!ft_strcmp(buf, KEY_UP))
		error = up_down_arrows(cur_record, cur_pos, UP);
	else if (!ft_strcmp(buf, KEY_DOWN))
		error = up_down_arrows(cur_record, cur_pos, DOWN);
	else if (!ft_strcmp(buf, KEY_LEFT))
		error = left_right_keys(cur_record, cur_pos, LEFT);
	else if (!ft_strcmp(buf, KEY_RIGHT))
		error = left_right_keys(cur_record, cur_pos, RIGHT);
	return (error);
}

int	backspace_key(t_dlist **cur_record, int *cur_pos)
{
	if (*cur_pos > 0)
	{
		if (tputs(tgetstr("le", 0), 1, ft_putchar))
			return (ERROR);
		if (tputs(tgetstr("dc", 0), 1, ft_putchar))
			return (ERROR);
		record_deletechar((*cur_record)->content, *cur_pos);
		(*cur_pos)--;
	}
	return (SUCCESSED);
}

int	plain_insert(t_dlist **cur_record, int *cur_pos, char ch)
{
	int i;

	tputs(tgetstr("dl", 0), 2, ft_putchar);
	ft_putstr_fd("minishell: ", 1);
	if (record_insertchar((*cur_record)->content, *cur_pos, ch))
		return (ERROR);
	ft_putstr_fd(((t_record*)(*cur_record)->content)->str, 1);
	i = *cur_pos + 1;
	while (((t_record*)(*cur_record)->content)->str[i] != '\0')
	{
		tputs(tgetstr("le", 0), 1, ft_putchar);
		i++;
	}
	(*cur_pos)++;
	return (SUCCESSED);
}

int	plain_keys(t_dlist **cur_record, int *cur_pos, char ch)
{
	int	tmp_len;

	tmp_len = ((t_record*)(*cur_record)->content)->len;
	if (*cur_pos != tmp_len)
	{
		if (plain_insert(cur_record, cur_pos, ch))
			return (ERROR);
	}
	else if (*cur_pos == tmp_len)
	{
		write(1, &ch, 1);
		if (record_addchar((*cur_record)->content, ch))
			return (ERROR);
		(*cur_pos)++;
	}
	return (SUCCESSED);
}
