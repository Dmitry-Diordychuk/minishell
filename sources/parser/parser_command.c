/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:06:54 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/24 20:10:49 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** cmd_word : WORD
**          ;
*/

int			cmd_word(t_dlist **wordlist, t_cmdtbl **table)
{
	if (*wordlist)
	{
		if (peek_word(*wordlist) & WORD)
		{
			add_simcmd(table);
			if (!errno)
				pass_words(wordlist,
				&((t_simcmd*)ft_dlst_getlast_data((*table)->rows))->argv_list);
		}
	}
	return (errno ? ERROR : SUCCESSED);
}

/*
** cmd_prefix : io_redirect
**            | cmd_prefix   io_redirect
**            ;
*/

int			cmd_prefix(t_dlist **wordlist, t_cmdtbl **table)
{
	int is_redirect;

	is_redirect = io_redirect(wordlist, table);
	if (!errno && is_redirect)
		cmd_prefix(wordlist, table);
	return (errno ? ERROR : SUCCESSED);
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

	is_arg = 0;
	if (*wordlist)
	{
		is_redirect = io_redirect(wordlist, table);
		if (!errno && peek_word(*wordlist) & WORD)
			is_arg = pass_words(wordlist,
				&((t_simcmd*)ft_dlst_getlast_data((*table)->rows))->argv_list);
		if (!errno && (is_redirect || is_arg))
			cmd_suffix(wordlist, table);
	}
	return (errno ? ERROR : SUCCESSED);
}

/*
** command   : cmd_prefix   cmd_word   cmd_suffix
**           | cmd_prefix   cmd_word
**           | cmd_prefix
**           ;
*/

int			command(t_dlist **wordlist, t_cmdtbl **table)
{
	if (!errno)
		cmd_prefix(wordlist, table);
	if (!errno)
		cmd_word(wordlist, table);
	if (!errno)
		cmd_suffix(wordlist, table);
	return (errno ? ERROR : SUCCESSED);
}
