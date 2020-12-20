/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 06:06:46 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/20 14:55:09 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *lexer_error_handler(t_list **tokens, char **tmp, int error)
{
	if (error == ALLOCATION_FAILED)
	{
		ft_lstclear(tokens, delete_token);
		free(*tmp);
		return (NULL);
	}
	free(*tmp);
	return (*tokens);
}

int	do_if_quotes(t_list **tokens, char **tmp, char *input,int *quote_status)
{
	int		error;

	if (((*input == '\'') && (*quote_status != WEAK_OPEN)) ||
		((*input == '"') && (*quote_status != STRONG_OPEN)))
	{
		error = try_add_word_token(tokens, tmp, *quote_status);
		if (*input == '\'' && *quote_status == CLOSE)
			*quote_status = STRONG_OPEN;
		else if (*input == '"' && *quote_status == CLOSE)
			*quote_status = WEAK_OPEN;
		else
			*quote_status = CLOSE;
		error = add_token(tokens, *input, NULL);
		if (error == ALLOCATION_FAILED)
			return (ALLOCATION_FAILED);
		return (TRUE);
	}
	return (FALSE);
}

int do_if_enviroment(t_list **tokens, char **tmp, char *input, int quote_status)
{
	int		error;

	if (*input == '$' && quote_status != STRONG_OPEN)
	{
		error = try_add_word_token(tokens, tmp, quote_status);
		if (*(input + 1) == '?')
			error = add_token(tokens, LAST_RESULT, NULL);
		else
			error = add_token(tokens, *input, NULL);
		if (error == ALLOCATION_FAILED)
			return (ALLOCATION_FAILED);
		return (TRUE);
	}
	return (FALSE);
}

int	do_if_other(t_list **tokens, char **tmp, char *input, int quote_status)
{
	int		error;

	if (strchr(";|<>", *input) && quote_status == CLOSE)
	{
		error = try_add_word_token(tokens, tmp, quote_status);
		if (*input == '>' && *(input + 1) == '>')
			error = add_token(tokens, GREATGREAT, NULL);
		else
			error = add_token(tokens, *input, NULL);
		if (error == ALLOCATION_FAILED)
			return (ALLOCATION_FAILED);
		return (TRUE);
	}
	return (FALSE);
}

t_list *run_lexer(char *input)
{
	t_list	*tokens;
	char	*tmp;
	int		quote;
	int		error;

	tokens = NULL;
	tmp = NULL;
	quote = CLOSE;
	error = SUCCESSED;
	while (*input != '\0')
	{
		if ((error = do_if_quotes(&tokens, &tmp, input, &quote)) ||
			(error = do_if_other(&tokens, &tmp, input, quote)) ||
			(error = do_if_enviroment(&tokens, &tmp, input, quote)))
			;
		else
			error = add_letter(&tmp, *input);
		if (error == ALLOCATION_FAILED)
			break;
		if ((((*input == '$') && (*(input + 1) == '?')) && quote != STRONG_OPEN) ||
			(((*input == '>') && (*(input + 1) == '>')) && quote == CLOSE))
			input++;
		input++;
	}
	error = try_add_word_token(&tokens, &tmp, quote);
	return (lexer_error_handler(&tokens, &tmp, error));
}
