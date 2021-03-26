/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:33:31 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/26 20:38:09 by kdustin          ###   ########.fr       */
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
	return (TOKEN_ERROR);
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
			msg("minishell: syntax error near unexpected token `newline'\n",
																	NULL, NULL);
			return (TOKEN_ERROR);
		}
		return (TRUE);
	}
	return (FALSE);
}

int			pipe_sequence(t_dlist **wordlist, t_cmdtbl **table)
{
	int		error;
	t_bool	is_pipe;

	error = 0;
	if (*wordlist != NULL)
	{
		error = command(wordlist, table);
		if (!error)
		{
			if ((is_pipe = pipe_op(wordlist)) < 0)
				error = TOKEN_ERROR;
		}
		if (!error && is_pipe)
			error = pipe_sequence(wordlist, table);
	}
	return (error ? error : SUCCESSED);
}

/*
** list : list   separator_op   pipe_sequence
**      |                       pipe_sequence
**      ;
*/

int			list(t_dlist **wordlist, t_cmdtbl **table)
{
	int error;

	error = 0;
	if (*wordlist != NULL)
	{
		if (peek_word(*wordlist) & SEPARATOR || peek_word(*wordlist) & PIPE)
		{
			if (peek_word(*wordlist) & SEPARATOR)
				msg("minishell: syntax error near unexpected token `;'", "\n",
																			0);
			if (peek_word(*wordlist) & PIPE)
				msg("minishell: syntax error near unexpected token `|'", "\n",
																			0);
			return (TOKEN_ERROR);
		}
		error = pipe_sequence(wordlist, table);
		if (peek_word(*wordlist) & SEPARATOR)
			ft_dlst_removefirst(wordlist, delete_word_desc);
	}
	return (error ? error : SUCCESSED);
}

int			run_parser(t_dlist **wordlist, t_cmdtbl **table)
{
	int error;

	error = 0;
	if (*wordlist)
	{
		if (!(*table = create_cmdtbl()))
			error = ALLOCATION_ERROR;
		if (!error && *wordlist != NULL)
			error = list(wordlist, table);
		if (error)
		{
			ft_dlst_clear(wordlist, delete_word_desc);
			*wordlist = NULL;
			delete_cmdtbl(*table);
			*table = NULL;
			return (error);
		}
	}
	return (SUCCESSED);
}
