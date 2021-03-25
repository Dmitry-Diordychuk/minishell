/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:04:25 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/25 14:40:25 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool		pass_words(t_dlist **wordlist, t_dlist **list)
{
	t_bool is_arg;

	is_arg = FALSE;
	while (*wordlist && peek_word(*wordlist) & WORD)
	{
		is_arg = TRUE;
		ft_dlst_append(list, ft_dlst_popfirst_elem(wordlist));
		if (*wordlist && !(peek_word(*wordlist) & ATTACH))
			break ;
	}
	return (is_arg);
}

void		init_redirection_fields(t_cmdtbl **table, t_dlist *filename_list,
														int io_redirection_op)
{
	if (io_redirection_op == (OPERATOR | LESS))
		(*table)->in_file_list = filename_list;
	else if (io_redirection_op == (OPERATOR | GREAT))
	{
		(*table)->out_file_list = filename_list;
		(*table)->is_append = 0;
	}
	else if (io_redirection_op == (OPERATOR | GREATGREAT))
	{
		(*table)->out_file_list = filename_list;
		(*table)->is_append = 1;
	}
}

/*
** filename : WORD
**          ;
*/

t_dlist		*init_name(int io_operator, t_cmdtbl **table)
{
	if (io_operator == (OPERATOR | LESS) && (*table)->in_file_list)
		return ((*table)->in_file_list);
	if (
	(io_operator == (OPERATOR | GREAT) ||
	io_operator == (OPERATOR | GREATGREAT)) &&
	(*table)->out_file_list)
		return ((*table)->out_file_list);
	return (NULL);
}

int			filename(t_dlist **wordlist, t_cmdtbl **table)
{
	t_dlist		*name;
	int			io_operator;
	int			error;

	error = 0;
	io_operator = peek_word(*wordlist);
	ft_dlst_removefirst(wordlist, delete_word_desc);
	if (*wordlist == NULL || peek_word(*wordlist) & OPERATOR)
		return (error_handler(wordlist));
	name = init_name(io_operator, table);
	if (peek_word(*wordlist) & WORD)
	{
		pass_words(wordlist, &name);
		error = add_word(&name, NULL, FILE_SEPARATOR);
	}
	else
	{
		errno = EIO;
		error = TOKEN_ERROR;
	}
	if (!error)
		init_redirection_fields(table, name, io_operator);
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

int			io_redirect(t_dlist **wordlist, t_cmdtbl **table)
{
	t_bool	is_flag;
	int		error;

	error = 0;
	is_flag = FALSE;
	while (!error && *wordlist)
	{
		if (peek_word(*wordlist) & LESS)
			error = filename(wordlist, table);
		else if (peek_word(*wordlist) & GREAT)
			error = filename(wordlist, table);
		else if (peek_word(*wordlist) & GREATGREAT)
			error = filename(wordlist, table);
		else
			break ;
		is_flag = TRUE;
	}
	if (error)
		return (error);
	return (is_flag);
}
