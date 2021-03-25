/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_recognize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 07:22:16 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/25 18:46:09 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	recognize_operator(t_dlist **wordlist, char **input_line)
{
	int error;

	error = 0;
	if (**input_line == ';')
		error = add_word(wordlist, NULL, OPERATOR | SEPARATOR);
	else if (**input_line == '|')
		error = add_word(wordlist, NULL, OPERATOR | PIPE);
	else if (**input_line == '>')
	{
		if (*(*input_line + 1) == '>')
		{
			(*input_line)++;
			error = add_word(wordlist, NULL, OPERATOR | GREATGREAT);
		}
		else
			error = add_word(wordlist, NULL, OPERATOR | GREAT);
	}
	else if (**input_line == '<')
		error = add_word(wordlist, NULL, OPERATOR | LESS);
	if (error)
		return (ALLOCATION_ERROR);
	(*input_line)++;
	return (SUCCESSED);
}

int	recognize_default(t_dlist **wordlist, char **input_line, int *attach)
{
	char	*word;
	int		error;

	error = 0;
	word = NULL;
	while (!ft_strchr("'\";|><$", **input_line) && !ft_isspace(**input_line) &&
	!error)
		if (**input_line == '\\')
			error = handle_backslash(&word, input_line);
		else
		{
			error = add_letter(&word, **input_line);
			(*input_line)++;
		}
	if (word != NULL && !error)
		error = add_word(wordlist, word, WORD | DEFAULT | *attach);
	if (error != 0)
	{
		free(word);
		return (error);
	}
	turn_on(attach);
	return (SUCCESSED);
}

int	recognize_single_quote(t_dlist **wordlist, char **input_line,
															int *attach)
{
	char	*word;
	int		error;

	error = 0;
	word = NULL;
	while (**input_line != '\'' && !error)
		if (**input_line == '\0')
			error = TOKEN_ERROR;
		else
		{
			error = add_letter(&word, **input_line);
			(*input_line)++;
		}
	if (word == NULL && !error)
		if (!(word = ft_strdup("")))
			error = ALLOCATION_ERROR;
	if (!error)
		error = add_word(wordlist, word, WORD | SQUOTE | *attach);
	if (error)
	{
		free(word);
		return (error);
	}
	turn_on(attach);
	return (SUCCESSED);
}

int	double_qoute_dollar(t_dlist **wordlist, char **input_line, int *attach,
																	char **word)
{
	int error;

	error = 0;
	if (*word != NULL)
		error = add_word(wordlist, *word, WORD | DQUOTE | *attach);
	if (*word != NULL)
	{
		*word = NULL;
		(*attach = 0);
	}
	if (!error)
		recognize_dollar(wordlist, input_line, WORD | DQUOTE, attach);
	*attach = 0;
	if (error)
		return (error);
	return (SUCCESSED);
}

int	recognize_double_quote(t_dlist **wordlist, char **input_line,
															int *attach)
{
	char	*word;
	t_bool	dollar_flag;
	int		error;

	error = 0;
	dollar_flag = FALSE;
	word = NULL;
	while (**input_line != '\"' && !error)
		if (**input_line == '\0')
			error = TOKEN_ERROR;
		else if (**input_line == '\\' && *(*input_line + 1) == '$')
			error = skip_dollar(input_line, &word);
		else if (**input_line == '$' && (dollar_flag = TRUE))
			error = double_qoute_dollar(wordlist, input_line, attach, &word);
		else if (!(error = add_letter(&word, **input_line)))
			(*input_line)++;
	if (!error && !dollar_flag && !(word) && !(word = ft_strdup("")))
		error = ALLOCATION_ERROR;
	if (!error && word)
		error = add_word(wordlist, word, 0xa40 | *attach);
	if (error)
		free(word);
	turn_on(attach);
	return (error ? error : SUCCESSED);
}
