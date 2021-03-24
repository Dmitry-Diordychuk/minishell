/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:33:31 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/24 22:08:29 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			error_handler(t_dlist **wordlist)
{
	msg("minishell: syntax error near unexpected token ", 0, 0);
	if (*wordlist == NULL)
		msg("`newline'\n", 0, 0);
	else if (peek_word(*wordlist) & PIPE)
		msg("`|'\n", 0, 0);
	else if (peek_word(*wordlist) & SEPARATOR)
		msg("`;'\n", 0, 0);
	else if (peek_word(*wordlist) & GREAT)
		msg("`>'\n", 0, 0);
	else if (peek_word(*wordlist) & GREATGREAT)
		msg("`>>'\n", 0, 0);
	else if (peek_word(*wordlist) & LESS)
		msg("`<'\n", 0, 0);
	errno = EIO;
	return (ERROR);
}

/*
** pipe_sequence :                         command
**               |   pipe_sequence   '|'   command
**               ;
*/

t_bool		pipe_op(t_dlist **wordlist)
{
	if (peek_word(*wordlist) & PIPE)
	{
		ft_dlst_removefirst(wordlist, delete_word_desc);
		if (*wordlist == NULL)
		{
			errno = EIO;
			msg("minishell: syntax error near unexpected token `newline'\n",
																	NULL, NULL);
			return (FALSE);
		}
		if (errno)
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

int			pipe_sequence(t_dlist **wordlist, t_cmdtbl **table)
{
	t_bool is_pipe;

	if (*wordlist != NULL)
	{
		command(wordlist, table);
		if (!errno)
			is_pipe = pipe_op(wordlist);
		if (!errno && is_pipe)
			pipe_sequence(wordlist, table);
		if (errno)
			return (ERROR);
	}
	return (SUCCESSED);
}

/*
** list : list   separator_op   pipe_sequence
**      |                       pipe_sequence
**      ;
*/

int			list(t_dlist **wordlist, t_cmdtbl **table)
{
	if (*wordlist != NULL)
	{
		if (peek_word(*wordlist) & SEPARATOR || peek_word(*wordlist) & PIPE)
		{
			if (peek_word(*wordlist) & SEPARATOR)
				msg("minishell: syntax error near unexpected token `;'", 0, 0);
			if (peek_word(*wordlist) & PIPE)
				msg("minishell: syntax error near unexpected token `|'", 0, 0);
			errno = EIO;
			return (ERROR);
		}
		pipe_sequence(wordlist, table);
		if (peek_word(*wordlist) & SEPARATOR)
			ft_dlst_removefirst(wordlist, delete_word_desc);
	}
	return (errno ? ERROR : SUCCESSED);
}

int			run_parser(t_dlist **wordlist, t_cmdtbl **table)
{
	if (*wordlist)
	{
		*table = create_cmdtbl();
		if (!errno && *wordlist != NULL)
			list(wordlist, table);
		if (errno)
		{
			ft_dlst_clear(wordlist, delete_word_desc);
			*wordlist = NULL;
			delete_cmdtbl(*table);
			*table = NULL;
			return (ERROR);
		}
	}
	return (SUCCESSED);
}
