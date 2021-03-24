/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:04:25 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/24 22:08:26 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool		pass_words(t_dlist **wordlist, t_dlist **list)
{
	t_bool is_arg;

	is_arg = FALSE;
	while (!errno && *wordlist && peek_word(*wordlist) & WORD)
	{
		is_arg = TRUE;
		ft_dlst_append(list, ft_dlst_popfirst_elem(wordlist));
		if (*wordlist && !(peek_word(*wordlist) & ATTACH))
			break ;
	}
	return (is_arg);
}

int			init_redirection_fields(t_cmdtbl **table, t_dlist *filename_list,
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
	return (errno ? ERROR : SUCCESSED);
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

	io_operator = peek_word(*wordlist);
	ft_dlst_removefirst(wordlist, delete_word_desc);
	if (*wordlist == NULL || peek_word(*wordlist) & OPERATOR)
		return (error_handler(wordlist));
	name = init_name(io_operator, table);
	if (peek_word(*wordlist) & WORD)
	{
		pass_words(wordlist, &name);
		if (add_word(&name, NULL, FILE_SEPARATOR))
		{
			ft_dlst_clear(&name, delete_word_desc);
			return (ERROR);
		}
	}
	else
		errno = EINVAL;
	if (!errno)
		init_redirection_fields(table, name, io_operator);
	if (errno)
		ft_dlst_clear(&name, delete_word_desc);
	return (errno ? ERROR : SUCCESSED);
}

/*
** io_redirect : <    filename
**             | >    filename
**             | >>   filename
**             ;
*/

int			io_redirect(t_dlist **wordlist, t_cmdtbl **table)
{
	t_bool is_flag;

	is_flag = FALSE;
	while (!errno && *wordlist)
	{
		if (peek_word(*wordlist) & LESS)
			filename(wordlist, table);
		else if (peek_word(*wordlist) & GREAT)
			filename(wordlist, table);
		else if (peek_word(*wordlist) & GREATGREAT)
			filename(wordlist, table);
		else
			break ;
		is_flag = TRUE;
	}
	return (is_flag);
}
