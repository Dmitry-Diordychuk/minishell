/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 06:06:46 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/20 10:38:48 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_letter(char **str, char c)
{
	size_t	i;
	char	*newstr;
	size_t len;

	if (*str != NULL)
		len = ft_strlen(*str) + 2;
	else
		len = 2;
	if (!(newstr = (char*)malloc(len * sizeof(char))))
		return (ALLOCATION_FAILED);
	i = 0;
	while (*str != NULL && (*str)[i] != '\0')
	{
		newstr[i] = (*str)[i];
		i++;
	}
	newstr[i++] = c;
	newstr[i] = '\0';
	free(*str);
	*str = newstr;
	return (SUCCESSED);
}

t_token	*create_token(int name, char *value)
{
	t_token *new_token;

	if (!(new_token = (t_token*)malloc(sizeof(t_token))))
		return (NULL);
	new_token->name = name;
	new_token->value = value;
	return (new_token);
}

int add_token(t_list **tokens, int name, char *value)
{
	t_token	*new_token;
	t_list	*new_elem;

	if (!(new_token = create_token(name, value)))
		return (ALLOCATION_FAILED);
	if (!(new_elem = ft_lstnew((void*)new_token)))
	{
		free(new_token);
		return (ALLOCATION_FAILED);
	}
	ft_lstpush(tokens, new_elem);
	return (SUCCESSED);
}

void delete_token(void *content)
{
	t_token *t;

	t = (t_token*)content;
	free(t->value);
	free(t);
	t->value = NULL;
	t = NULL;
}

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



int	get_word(char **src, char **dest)
{
	if (*src != NULL)
	{
		if (!(*dest = ft_strdup(*src)))
			return (ALLOCATION_FAILED);
		free(*src);
		*src = NULL;
		return (SUCCESSED);
	}
	return (FAILED);
}

int	do_if_quotes(t_list **tokens, char **tmp, char *input,int *quote_status)
{
	int		get_word_result;
	char	*value;
	int		error;

	if (strchr("\"'", *input))
	{
		if ((get_word_result = get_word(tmp, &value)) == ALLOCATION_FAILED)
			return (ALLOCATION_FAILED);
		if (get_word_result == SUCCESSED)
			error = add_token(tokens, WORD, value);
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
	int		get_word_result;
	char	*value;
	int		error;

	if (*input == '$' && quote_status != STRONG_OPEN)
	{
		if (quote_status == WEAK_OPEN)
		{
			if ((get_word_result = get_word(tmp, &value)) == ALLOCATION_FAILED)
				return (ALLOCATION_FAILED);
			if (get_word_result == SUCCESSED)
				error = add_token(tokens, WORD, value);
		}
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
	int		get_world_result;
	char	*value;
	int		error;

	if (strchr(";|<>", *input) && quote_status == CLOSE)
	{
		if ((get_world_result = get_word(tmp, &value)) == ALLOCATION_FAILED)
			return (ALLOCATION_FAILED);
		if (get_world_result == SUCCESSED)
			error = add_token(tokens, WORD, value);
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
		if ((error = do_if_quotes(&tokens, &tmp, input, &quote)))
			;
		else if ((error = do_if_other(&tokens, &tmp, input, quote)))
			;
		else if ((error = do_if_enviroment(&tokens, &tmp, input, quote)))
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
	return (lexer_error_handler(&tokens, &tmp, error));
}
