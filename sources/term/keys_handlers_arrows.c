/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handlers_arrows.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:24:55 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/24 20:26:24 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	up_down_arrows(t_dlist **cur_record, int *cur_pos, int direction)
{
	size_t i;

	if (tputs(tgetstr("rc", 0), 1, ft_putchar))
		return (ERROR);
	if (tputs(tgetstr("dl", 0), 1, ft_putchar))
		return (ERROR);
	i = 0;
	while (i++ < ft_strlen("minishell: "))
		if (tputs(tgetstr("le", 0), 1, ft_putchar))
			return (ERROR);
	ft_putstr_fd("minishell: ", 1);
	if (direction == UP && (*cur_record)->next)
		*cur_record = (*cur_record)->next;
	else if (direction == DOWN && (*cur_record)->prev)
		*cur_record = (*cur_record)->prev;
	ft_putstr_fd(((t_record*)(*cur_record)->content)->str, 1);
	*cur_pos = ((t_record*)(*cur_record)->content)->len;
	return (SUCCESSED);
}

int	left_right_keys(t_dlist **cur_record, int *cur_pos, int direction)
{
	if (direction == LEFT)
	{
		if (*cur_pos > 0)
		{
			if (tputs(tgetstr("le", 0), 1, ft_putchar))
				return (ERROR);
			(*cur_pos)--;
		}
	}
	else if (direction == RIGHT)
		if (*cur_pos < ((t_record*)(*cur_record)->content)->len)
		{
			if (tputs(tgetstr("nd", 0), 1, ft_putchar))
				return (ERROR);
			(*cur_pos)++;
		}
	return (SUCCESSED);
}
