/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 11:17:03 by kdustin           #+#    #+#             */
/*   Updated: 2021/01/05 19:07:19 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (t != NULL)
		free(t->value);
	free(t);
}

int try_add_word_token(t_list **tokens, char **tmp, int quote)
{
	int		get_world_result;
	char	*value;

	value = NULL;
	if ((get_world_result = get_word(tmp, &value, quote)) == ALLOCATION_FAILED)
		return (ALLOCATION_FAILED);
	if (get_world_result == SUCCESSED)
		return(add_token(tokens, WORD, value));
	return (FAILED);
}
