/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 11:17:03 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/25 11:44:02 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_worddesc	*create_word(char *word, int flags)
{
	t_worddesc *new_word_desc;

	if (!(new_word_desc = (t_worddesc*)malloc(sizeof(t_worddesc))))
	{
		errno = ENOMEM;
		return (NULL);
	}
	new_word_desc->word = word;
	new_word_desc->flags = flags;
	return (new_word_desc);
}

int			add_word(t_dlist **word_list, char *word, int flags)
{
	t_worddesc	*new_word_desc;
	t_dlist		*new_list_elem;

	if (!(new_word_desc = create_word(word, flags)))
		return (ERROR);
	if (!(new_list_elem = ft_dlst_new(new_word_desc)))
	{
		free(new_word_desc);
		errno = ENOMEM;
		return (ERROR);
	}
	ft_dlst_append(word_list, new_list_elem);
	return (SUCCESSED);
}

void		delete_word_desc(void *content)
{
	t_worddesc *word_desc;

	word_desc = (t_worddesc*)content;
	if (word_desc != NULL)
		free(word_desc->word);
	free(word_desc);
}

int			peek_word(t_dlist *word_list)
{
	t_worddesc *first_word;

	if (word_list != NULL)
	{
		first_word = ft_dlst_getfirst_data(word_list);
		return (first_word->flags);
	}
	return (0);
}

char		*pop_word(t_dlist **wordlist)
{
	t_worddesc	*worddesc;
	char		*word;

	worddesc = (t_worddesc*)ft_dlst_popfirst_data(wordlist);
	word = worddesc->word;
	free(worddesc);
	return (word);
}
