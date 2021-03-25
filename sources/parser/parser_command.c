/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:06:54 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/25 14:38:06 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** cmd_word : WORD
**          ;
*/

int			cmd_word(t_dlist **wordlist, t_cmdtbl **table)
{
	int error;

	error = 0;
	if (*wordlist)
	{
		if (peek_word(*wordlist) & WORD)
		{
			error = add_simcmd(table);
			if (!error)
				pass_words(wordlist,
				&((t_simcmd*)ft_dlst_getlast_data((*table)->rows))->argv_list);
		}
	}
	return (error ? error : SUCCESSED);
}

/*
** cmd_prefix : io_redirect
**            | cmd_prefix   io_redirect
**            ;
*/

int			cmd_prefix(t_dlist **wordlist, t_cmdtbl **table)
{
	int	is_redirect;
	int	error;

	error = 0;
	if ((is_redirect = io_redirect(wordlist, table)) < 0)
	{
		if (errno == ENOMEM)
			error = ALLOCATION_ERROR;
		else if (errno == EIO)
			error = TOKEN_ERROR;
	}
	if (!error && is_redirect)
		error = cmd_prefix(wordlist, table);
	return (error ? error : SUCCESSED);
}

/*
** cmd_suffix : io_redirect
**            | cmd_suffix   io_redirect
**            |              WORD
**            | cmd_suffix   WORD
**            ;
*/

int			cmd_suffix(t_dlist **wordlist, t_cmdtbl **table)
{
	int is_redirect;
	int is_arg;
	int error;

	error = 0;
	is_arg = 0;
	if (*wordlist)
	{
		if ((is_redirect = io_redirect(wordlist, table)) < 0)
		{
			if (errno == ENOMEM)
				error = ALLOCATION_ERROR;
			else if (errno == EIO)
				error = TOKEN_ERROR;
		}
		if (!error && peek_word(*wordlist) & WORD)
			is_arg = pass_words(wordlist,
				&((t_simcmd*)ft_dlst_getlast_data((*table)->rows))->argv_list);
		if (!error && (is_redirect || is_arg))
			error = cmd_suffix(wordlist, table);
	}
	return (error ? error : SUCCESSED);
}

/*
** command   : cmd_prefix   cmd_word   cmd_suffix
**           | cmd_prefix   cmd_word
**           | cmd_prefix
**           ;
*/

int			command(t_dlist **wordlist, t_cmdtbl **table)
{
	int error;

	error = 0;
	error = cmd_prefix(wordlist, table);
	if (!error)
		error = cmd_word(wordlist, table);
	if (!error)
		error = cmd_suffix(wordlist, table);
	return (error ? error : SUCCESSED);
}
