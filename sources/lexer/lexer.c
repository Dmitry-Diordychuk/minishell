/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 06:06:46 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/27 13:43:03 by kdustin          ###   ########.fr       */
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

int	do_if_quotes(t_list **tokens, char **tmp, char *input,int *quote)
{
	int		error;

	if (ft_strchr("'\"", *input) && *quote == SLASH_OPEN)
		*quote = CLOSE;
	else if ((((*input == '\'') && (*quote != WEAK_OPEN)) ||
		((*input == '"') && (*quote != STRONG_OPEN))))
	{
		error = try_add_word_token(tokens, tmp, *quote);
		if (*input == '\'' && *quote == CLOSE)
			*quote = STRONG_OPEN;
		else if (*input == '"' && *quote == CLOSE)
			*quote = WEAK_OPEN;
		else
			*quote = CLOSE;
		error = add_token(tokens, *input, NULL);
		if (error == ALLOCATION_FAILED)
			return (ALLOCATION_FAILED);
		return (TRUE);
	}
	else if (*input == '\\' && *quote != STRONG_OPEN)
		*quote = SLASH_OPEN;
	//else if (*input == '\'' && *quote != STRONG_QUOTE)
	//	if (try_add_word_token(tokens, tmp, *quote) == ALLOCATION_FAILED)
	//		return (ALLOCATION_FAILED);
	return (FALSE);
}

int do_if_enviroment(t_list **tokens, char **tmp, char *input, int quote)
{
	int		error;

	if (*input == '$' && quote == SLASH_OPEN)
		quote = CLOSE;
	else if (*input == '$' && quote != STRONG_OPEN)
	{
		error = try_add_word_token(tokens, tmp, quote);
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

int	do_if_other(t_list **tokens, char **tmp, char *input, int quote)
{
	int		error;

	if (ft_strchr(";|<>", *input) && quote == STRONG_OPEN)
		quote = CLOSE;
	if (ft_strchr(";|<>", *input) && quote == CLOSE)
	{
		error = try_add_word_token(tokens, tmp, quote);
		if (*input == '>' && *(input + 1) == '>')
			error = add_token(tokens, GREATGREAT, NULL);
		else
			error = add_token(tokens, *input, NULL);
		if (error == ALLOCATION_FAILED)
			return (ALLOCATION_FAILED);
		return (TRUE);
	}
	else if (*input == ' ' && quote == CLOSE)
		if (try_add_word_token(tokens, tmp, quote) == ALLOCATION_FAILED)
			return (ALLOCATION_FAILED);
	return (FALSE);
}

int	get_token_size(char *input, int quote)
{
	if ((((*input == '$') && (*(input + 1) == '?')) && quote != STRONG_OPEN) ||
		(((*input == '>') && (*(input + 1) == '>')) && quote == CLOSE))
		return (2);
	return (1);
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
	while (*input != '\0')
	{
		if ((error = do_if_quotes(&tokens, &tmp, input, &quote)) ||
			(error = do_if_other(&tokens, &tmp, input, quote)) ||
			(error = do_if_enviroment(&tokens, &tmp, input, quote)))
			;
		else if (*input != '\\' || (*input == '\\' && quote != SLASH_OPEN))
			error = add_letter(&tmp, *input);
		if (error == ALLOCATION_FAILED)
			break;
		input = input + get_token_size(input, quote);
	}
	error = try_add_word_token(&tokens, &tmp, quote);
	return (lexer_error_handler(&tokens, &tmp, error));
}
