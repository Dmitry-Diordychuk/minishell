/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 06:06:46 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/29 22:37:09 by kdustin          ###   ########.fr       */
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
	//*tmp = NULL;
	return (*tokens);
}

int	do_if_quotes(t_list **tokens, char **tmp, const char *input,int *quote)
{
	int		error;

	if (((*input == '\'') && (*quote != WEAK_OPEN) && (*quote != SLASH_OPEN)) ||
		((*input == '"') && (*quote != STRONG_OPEN) && (*quote != SLASH_OPEN)))
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
	else if (*input == '\\' && *quote != STRONG_OPEN && *quote != SLASH_OPEN)
	{
		if (*quote == WEAK_OPEN && *(input + 1) != '$' && *(input + 1) != '"')
			return (FALSE);
		*quote = SLASH_OPEN;
		return (TRUE);
	}
	return (FALSE);
}

int do_if_enviroment(t_list **tokens, char **tmp, const char *input, int quote)
{
	int		error;

	if (*input == '$' && quote != STRONG_OPEN && quote != SLASH_OPEN)
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

int	do_if_other(t_list **tokens, char **tmp, const char *input, int *quote)
{
	int			error;

	if (strchr(";|<>", *input) && *quote == CLOSE)
	{
		error = try_add_word_token(tokens, tmp, *quote);
		if (*input == '>' && *(input + 1) == '>')
			error = add_token(tokens, GREATGREAT, NULL);
		else
			error = add_token(tokens, *input, NULL);
		if (error == ALLOCATION_FAILED)
			return (ALLOCATION_FAILED);
		return (TRUE);
	}
	else if (ft_isspace(*input) && *quote == CLOSE)
	{
		if (try_add_word_token(tokens, tmp, *quote) == ALLOCATION_FAILED)
			return (ALLOCATION_FAILED);
		if (*tokens != NULL)
			if (((t_token*)ft_lstlast(*tokens)->content)->name != BLANK)
				if (add_token(tokens, BLANK, NULL) == ALLOCATION_FAILED)
					return (ALLOCATION_FAILED);
		return (TRUE);
	}
	return (FALSE);
}

int	get_token_size(const char *input, int quote)
{
	if ((((*input == '$') && (*(input + 1) == '?')) && quote != STRONG_OPEN) ||
		(((*input == '>') && (*(input + 1) == '>')) && quote == CLOSE))
		return (2);
	return (1);
}

t_list *run_lexer(const char *input)
{
	t_list	*tokens;
	char	*tmp;
	int		quote;
	int		error;
	int		prev_quote;

	if (input == NULL)
		return (NULL);
	tokens = NULL;
	tmp = NULL;
	quote = CLOSE;
	prev_quote = CLOSE;
	while (*input != '\0')
	{
		if ((error = do_if_quotes(&tokens, &tmp, input, &quote)) ||
			(error = do_if_other(&tokens, &tmp, input, &quote)) ||
			(error = do_if_enviroment(&tokens, &tmp, input, quote)))
			;
		else if (ft_isspace(*input) && quote == SLASH_OPEN)
		{
			error = try_add_word_token(&tokens, &tmp, quote);
			if (error == ALLOCATION_FAILED)
				break;
			if (tmp == NULL && *input == ' ')
				if (add_token(&tokens, WORD, ft_strdup("")) == ALLOCATION_FAILED)
					return (NULL);
			error = add_token(&tokens, BLANK, NULL);
			quote = prev_quote;
		}
		else
		{
			error = add_letter(&tmp, *input);
			if (quote == SLASH_OPEN)
				quote = prev_quote;
		}
		if (error == ALLOCATION_FAILED)
			break;
		if (quote != SLASH_OPEN)
			prev_quote = quote;
		input = input + get_token_size(input, quote);
	}
	error = try_add_word_token(&tokens, &tmp, quote);
	return (lexer_error_handler(&tokens, &tmp, error));
}
