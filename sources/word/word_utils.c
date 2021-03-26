/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:38:30 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/26 23:02:49 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		wordjoin(char **dest, char *src)
{
	char *temp;

	if (*dest == NULL)
	{
		if (!(temp = ft_strdup(src)))
		{
			free(src);
			errno = ENOMEM;
			return (ALLOCATION_ERROR);
		}
	}
	else
	{
		if (!(temp = ft_strjoin(*dest, src)))
		{
			free(*dest);
			free(src);
			errno = ENOMEM;
			return (ALLOCATION_ERROR);
		}
	}
	free(*dest);
	free(src);
	*dest = temp;
	return (SUCCESSED);
}

char	*get_env_word(t_dlist **wordlist, char **envp, int *last_return)
{
	char *name;
	char *value;

	name = pop_word(wordlist);
	if (name[1] == '?')
		value = ft_itoa(*last_return);
	else if (name[1] == '\0')
		value = ft_strdup(name);
	else
		value = find_env_var(envp, name + 1);
	free(name);
	while (*wordlist != NULL && peek_word(*wordlist) & ATTACH &&
									peek_word(*wordlist) & DOLLAR)
	{
		name = pop_word(wordlist);
		if (name[1] == '?')
			wordjoin(&value, ft_itoa(*last_return));
		else if (name[1] == '\0')
			wordjoin(&value, ft_strdup(name));
		else
			wordjoin(&value, find_env_var(envp, name + 1));
		free(name);
	}
	return (errno ? NULL : value);
}

char	*glue_dquote(t_dlist **wordlist, char **envp, int *last_return)
{
	char	*dq_glued;
	int		error;

	error = 0;
	dq_glued = NULL;
	while (peek_word(*wordlist) & DQUOTE)
	{
		if (!(*wordlist) || peek_word(*wordlist) & CLOSED)
		{
			if (peek_word(*wordlist) & DOLLAR)
				error = wordjoin(&dq_glued, get_env_word(wordlist, envp,
																last_return));
			else
				error = wordjoin(&dq_glued, pop_word(wordlist));
			break ;
		}
		if (peek_word(*wordlist) & DOLLAR)
			error = wordjoin(&dq_glued, get_env_word(wordlist, envp,
																last_return));
		else
			error = wordjoin(&dq_glued, pop_word(wordlist));
	}
	if (error)
		free(dq_glued);
	return (error ? NULL : dq_glued);
}

char	*glue_words(t_dlist **wordlist, char **envp, int *last_return)
{
	char	*words;
	int		error;

	error = 0;
	words = NULL;
	while (!error && *wordlist && peek_word(*wordlist) & WORD)
	{
		if (peek_word(*wordlist) & DQUOTE)
			error = wordjoin(&words, glue_dquote(wordlist, envp, last_return));
		else if (peek_word(*wordlist) & DOLLAR)
			error = wordjoin(&words, get_env_word(wordlist, envp, last_return));
		else
			error = wordjoin(&words, pop_word(wordlist));
		if (*wordlist && !(peek_word(*wordlist) & ATTACH))
			break ;
	}
	if (error)
		free(words);
	return (error ? NULL : words);
}
