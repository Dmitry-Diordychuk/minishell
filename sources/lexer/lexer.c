/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 06:06:46 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/24 21:48:20 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			recognize_dollar(t_dlist **wordlist, char **input_line, int flag,
															int *attach_flag)
{
	char *word;

	if (errno != 0)
		return (ERROR);
	if ((*(*input_line + 1) == '\'' || *(*input_line + 1) == '"') &&
	(flag & DEFAULT || flag == (WORD | DOLLAR)))
	{
		(*input_line)++;
		return (SUCCESSED);
	}
	word = NULL;
	add_letter(&word, **input_line);
	while ((*input_line)++ && errno == 0 &&
	!ft_strchr("'\"\\;|><\t\n\v\f\r $=:", **input_line))
		add_letter(&word, **input_line);
	if (errno == 0 && flag & DQUOTE && **input_line == '"')
		add_word(wordlist, word, flag | DOLLAR | CLOSED);
	else if (errno == 0)
		add_word(wordlist, word, flag | DOLLAR | *attach_flag);
	if (errno != 0)
		free(word);
	turn_on(attach_flag);
	return (errno ? ERROR : SUCCESSED);
}

/*
**	return in g_wordlist
*/

int			run_lexer(t_dlist **wordlist, char *input_line)
{
	int attach;

	attach = 0;
	wind_off(&input_line);
	while (*input_line != '\0' && errno == 0)
	{
		if (*input_line == '\'' || *input_line == '"')
		{
			input_line++;
			if (*(input_line - 1) == '\'')
				recognize_single_quote(wordlist, &input_line, &attach);
			else if (*(input_line - 1) == '"')
				recognize_double_quote(wordlist, &input_line, &attach);
			input_line++;
		}
		else if (ft_strchr(";|><", *input_line) && *input_line != '\0')
			recognize_operator(wordlist, &input_line);
		else if (*input_line == '$')
			recognize_dollar(wordlist, &input_line, WORD | DOLLAR, &attach);
		else if (!ft_isspace(*input_line))
			recognize_default(wordlist, &input_line, &attach);
		else if (!(attach = 0))
			input_line++;
	}
	return (errno ? ERROR : SUCCESSED);
}
