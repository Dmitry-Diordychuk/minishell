/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 06:06:46 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/25 18:46:33 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			lexer_handle_exit(int error, t_dlist **wordlist)
{
	if (error)
		ft_dlst_clear(wordlist, delete_word_desc);
	if (error == TOKEN_ERROR)
		msg("minishell: syntax error near unexpected token `newline'\n", 0, 0);
	return (error);
}

int			handle_backslash(char **word, char **input_line)
{
	(*input_line)++;
	if (**input_line == '\0')
	{
		msg("minishell: syntax error near unexpected token `newline'\n", 0, 0);
		return (TOKEN_ERROR);
	}
	if (add_letter(word, **input_line) < 0)
		return (ALLOCATION_ERROR);
	(*input_line)++;
	return (SUCCESSED);
}

int			recognize_dollar(t_dlist **wordlist, char **input_line, int flag,
															int *attach_flag)
{
	char	*word;
	int		error;

	error = 0;
	if ((*(*input_line + 1) == '\'' || *(*input_line + 1) == '"') &&
	(flag & DEFAULT || flag == (WORD | DOLLAR)))
	{
		(*input_line)++;
		return (SUCCESSED);
	}
	word = NULL;
	error = add_letter(&word, **input_line);
	while (!error && (*input_line)++ &&
	!ft_strchr("'\"\\;|>< $=:", **input_line))
		error = add_letter(&word, **input_line);
	if (!error && flag & DQUOTE && **input_line == '"')
		error = add_word(wordlist, word, flag | DOLLAR | CLOSED);
	else if (!error)
		error = add_word(wordlist, word, flag | DOLLAR | *attach_flag);
	if (error)
		free(word);
	turn_on(attach_flag);
	return (error ? error : SUCCESSED);
}

int			recognize_quotes(t_dlist **wordlist, char **input_line, int *attach)
{
	int error;

	error = 0;
	if (*((*input_line) - 1) == '\'')
		error = recognize_single_quote(wordlist, input_line, attach);
	else if (*((*input_line) - 1) == '"')
		error = recognize_double_quote(wordlist, input_line, attach);
	return (error ? error : SUCCESSED);
}

int			run_lexer(t_dlist **wordlist, char *input_line)
{
	int attach;
	int error;

	error = 0;
	attach = 0;
	wind_off(&input_line);
	while (*input_line != '\0' && !error)
	{
		if (*input_line == '\'' || *input_line == '"')
		{
			input_line++;
			error = recognize_quotes(wordlist, &input_line, &attach);
			input_line++;
		}
		else if (ft_strchr(";|><", *input_line) && *input_line != '\0')
			error = recognize_operator(wordlist, &input_line);
		else if (*input_line == '$')
			error = recognize_dollar(wordlist, &input_line, WORD | DOLLAR,
																	&attach);
		else if (!ft_isspace(*input_line))
			error = recognize_default(wordlist, &input_line, &attach);
		else if (!(attach = 0))
			input_line++;
	}
	return (lexer_handle_exit(error, wordlist));
}
