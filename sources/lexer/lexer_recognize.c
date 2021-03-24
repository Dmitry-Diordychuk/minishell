/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_recognize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 07:22:16 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/24 22:08:20 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	recognize_operator(t_dlist **wordlist, char **input_line)
{
	if (**input_line == ';')
		add_word(wordlist, NULL, OPERATOR | SEPARATOR);
	else if (**input_line == '|')
		add_word(wordlist, NULL, OPERATOR | PIPE);
	else if (**input_line == '>')
	{
		if (*(*input_line + 1) == '>')
		{
			(*input_line)++;
			add_word(wordlist, NULL, OPERATOR | GREATGREAT);
		}
		else
			add_word(wordlist, NULL, OPERATOR | GREAT);
	}
	else if (**input_line == '<')
		add_word(wordlist, NULL, OPERATOR | LESS);
	(*input_line)++;
	return (errno ? ERROR : SUCCESSED);
}

int	recognize_default(t_dlist **wordlist, char **input_line, int *attach_flag)
{
	char	*word;

	word = NULL;
	while (!ft_strchr("'\";|><$", **input_line) && !ft_isspace(**input_line) &&
	errno == 0)
		if (**input_line == '\\')
			handle_backslash(&word, input_line);
		else if (!add_letter(&word, **input_line))
			(*input_line)++;
	if (word != NULL && errno == 0)
		add_word(wordlist, word, WORD | DEFAULT | *attach_flag);
	if (errno != 0)
		free(word);
	turn_on(attach_flag);
	return (errno ? ERROR : SUCCESSED);
}

int	recognize_single_quote(t_dlist **wordlist, char **input_line,
															int *attach_flag)
{
	char	*word;

	word = NULL;
	while (**input_line != '\'' && errno == 0)
		if (**input_line == '\0')
			errno = EIO;
		else
		{
			add_letter(&word, **input_line);
			(*input_line)++;
		}
	if (errno == 0 && word == NULL)
		if (!(word = ft_strdup("")))
			errno = ENOMEM;
	if (errno == 0)
		add_word(wordlist, word, WORD | SQUOTE | *attach_flag);
	if (errno != 0)
		free(word);
	turn_on(attach_flag);
	return (errno ? ERROR : SUCCESSED);
}

int	close_qoute(t_dlist **wordlist, int dollar_flag, char **word,
															int *attach_flag)
{
	if (!errno && !dollar_flag && !(*word) && !(*word = ft_strdup("")))
		errno = ENOMEM;
	if (!errno && *word)
		add_word(wordlist, *word, 0xa40 | *attach_flag);
	return (errno ? ERROR : SUCCESSED);
}

int	recognize_double_quote(t_dlist **wordlist, char **input_line,
															int *attach_flag)
{
	char	*word;
	t_bool	dollar_flag;

	dollar_flag = FALSE;
	word = NULL;
	while (**input_line != '\"' && errno == 0)
		if (**input_line == '\0')
			errno = EIO;
		else if (**input_line == '$')
		{
			if ((dollar_flag = TRUE) && word != NULL)
				add_word(wordlist, word, WORD | DQUOTE | *attach_flag);
			if ((word != NULL && !(word = NULL)))
				(*attach_flag = 0);
			recognize_dollar(wordlist, input_line, WORD | DQUOTE, attach_flag);
			*attach_flag = 0;
		}
		else if (**input_line == '\\')
			handle_backslash(&word, input_line);
		else if (!add_letter(&word, **input_line))
			(*input_line)++;
	close_qoute(wordlist, dollar_flag, &word, attach_flag);
	errno ? free(word) : turn_on(attach_flag);
	return (errno ? ERROR : SUCCESSED);
}
