/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:04:25 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/26 20:52:19 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool		pass_words(t_dlist **wordlist, t_dlist **list)
{
	t_bool	is_arg;
	t_dlist	*pop;

	is_arg = FALSE;
	while (*wordlist && peek_word(*wordlist) & WORD)
	{
		is_arg = TRUE;
		pop = ft_dlst_popfirst_elem(wordlist);
		ft_dlst_append(list, pop);
		if (wordlist && *wordlist && !(peek_word(*wordlist) & ATTACH))
			break ;
	}
	return (is_arg);
}

void		init_redirection_fields(t_simcmd *simcmd, t_dlist *filename_list,
														int io_redirection_op)
{
	if (io_redirection_op == (OPERATOR | LESS))
		simcmd->in_file_list = filename_list;
	else if (io_redirection_op == (OPERATOR | GREAT))
	{
		simcmd->out_file_list = filename_list;
		simcmd->is_append = 0;
	}
	else if (io_redirection_op == (OPERATOR | GREATGREAT))
	{
		simcmd->out_file_list = filename_list;
		simcmd->is_append = 1;
	}
}

/*
** filename : WORD
**          ;
*/

t_dlist		*init_name(int io_operator, t_simcmd *simcmd)
{
	if (io_operator == (OPERATOR | LESS) && simcmd->in_file_list)
		return (simcmd->in_file_list);
	if (
	(io_operator == (OPERATOR | GREAT) ||
	io_operator == (OPERATOR | GREATGREAT)) &&
	simcmd->out_file_list)
		return (simcmd->out_file_list);
	return (NULL);
}

int			filename(t_dlist **wordlist, t_simcmd *simcmd)
{
	t_dlist		*name;
	int			io_operator;
	int			error;

	error = 0;
	io_operator = peek_word(*wordlist);
	ft_dlst_removefirst(wordlist, delete_word_desc);
	if (*wordlist == NULL || peek_word(*wordlist) & OPERATOR)
		return (error_handler(wordlist));
	name = init_name(io_operator, simcmd);
	if (peek_word(*wordlist) & WORD)
	{
		pass_words(wordlist, &name);
		error = add_word(&name, NULL, FILE_SEPARATOR);
	}
	else
		error = TOKEN_ERROR;
	if (!error)
		init_redirection_fields(simcmd, name, io_operator);
	if (error)
		ft_dlst_clear(&name, delete_word_desc);
	return (error ? error : SUCCESSED);
}

/*
** io_redirect : <    filename
**             | >    filename
**             | >>   filename
**             ;
*/

int			io_redirect(t_dlist **wordlist, t_simcmd *simcmd)
{
	t_bool	is_flag;
	int		error;

	error = 0;
	is_flag = FALSE;
	while (!error && *wordlist)
	{
		if (peek_word(*wordlist) & LESS)
			error = filename(wordlist, simcmd);
		else if (peek_word(*wordlist) & GREAT)
			error = filename(wordlist, simcmd);
		else if (peek_word(*wordlist) & GREATGREAT)
			error = filename(wordlist, simcmd);
		else
			break ;
		is_flag = TRUE;
	}
	if (error)
		return (error);
	return (is_flag);
}
