/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:07:28 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/26 16:36:49 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_result_copy(t_dlist **cur_record, t_dlist **history)
{
	char *output;

	if (!(output = ft_strdup(((t_record*)(*cur_record)->content)->str)))
		return (NULL);
	if (((t_record*)(*cur_record)->content)->str[0] == '\0')
		ft_dlst_removefirst(history, delete_record);
	else if ((*cur_record)->prev != NULL)
	{
		ft_dlst_removefirst(history, delete_record);
		if (add_record(history, output))
			return (NULL);
	}
	*cur_record = NULL;
	return (output);
}

int		read_loop(t_dlist **cur_record, t_data *data, t_dlist **history)
{
	char	ch;
	int		cur_pos;
	int		error;

	error = 0;
	cur_pos = 0;
	while (read(0, &ch, 1))
		if (ch == '\x03')
			error = signal_c_key(cur_record, history, &cur_pos, data);
		else if (ch == CTRL_D && ((t_record*)(*cur_record)->content)->len == 0)
		{
			write(1, "exit", 5);
			data->last_return = 0;
			data->is_exit = TRUE;
			break ;
		}
		else if (ch == '\e')
			error = special_keys(cur_record, &cur_pos);
		else if (ch == '\177')
			error = backspace_key(cur_record, &cur_pos);
		else if (ch == '\n')
			break ;
		else if (ft_isprint(ch))
			error = plain_keys(cur_record, &cur_pos, ch);
	return (error);
}

int		apply_func(t_dlist **history, int (*fun)(t_record *record))
{
	t_diter iter;

	ft_diter_init(history, &iter);
	while (ft_diter_more(&iter))
		if (fun((t_record*)ft_diter_getnext(&iter)))
			return (ERROR);
	return (SUCCESSED);
}

int		readline(char **output, t_dlist **history, t_data *data)
{
	t_dlist	*cur_record;

	if (apply_func(history, save_str))
		return (ALLOCATION_ERROR);
	if (add_record(history, ""))
		return (ALLOCATION_ERROR);
	cur_record = *history;
	if (init_terminal_data())
		return (ERROR);
	if (set_terminal_options(ON))
		return (ERROR);
	if (tputs(tgetstr("ks", 0), 1, ft_putchar))
		return (ERROR);
	if (tputs(tgetstr("sc", 0), 1, ft_putchar))
		return (ERROR);
	if (read_loop(&cur_record, data, history))
		return (ERROR);
	if (set_terminal_options(OFF))
		return (ERROR);
	ft_putchar('\n');
	if (!(*output = get_result_copy(&cur_record, history)))
		return (ALLOCATION_ERROR);
	if (apply_func(history, reset_str))
		return (ALLOCATION_ERROR);
	return (SUCCESSED);
}
