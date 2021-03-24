/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:35:12 by ebarra            #+#    #+#             */
/*   Updated: 2021/03/20 21:00:15 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		sorting_list_env(t_list **tl, int size)
{
	int			i;
	t_list		*tmp;
	char		*s1;
	char		*s2;
	char		*tmp2;

	i = 0;
	while (i < size)
	{
		tmp = *tl;
		while (tmp->next)
		{
			s1 = tmp->content;
			s2 = tmp->next->content;
			if (ft_strcmp(s1, s2) > 0)
			{
				tmp2 = tmp->content;
				tmp->content = tmp->next->content;
				tmp->next->content = tmp2;
			}
			tmp = tmp->next;
		}
		i++;
	}
}

static void		del_content(void *content)
{
	char		*s;

	s = (char*)content;
	free(s);
}

static t_list	*copy_env_to_tlist(char **env)
{
	int			i;
	t_list		*new;
	t_list		*tmp;
	char		*env_i_copy;

	i = -1;
	tmp = NULL;
	while (env[++i])
	{
		if (!(env_i_copy = ft_strdup(env[i])))
		{
			ft_lstclear(&tmp, del_content);
			errno = ENOMEM;
			return (NULL);
		}
		if (!(new = ft_lstnew(env_i_copy)))
		{
			free(env_i_copy);
			ft_lstclear(&tmp, del_content);
			errno = ENOMEM;
			return (NULL);
		}
		ft_lstadd_back(&tmp, new);
	}
	return (tmp);
}

static void		print_export_woo(void *content)
{
	char		*s;
	int			i;
	char		*s1;
	char		*s2;

	s = (char*)content;
	if ((s[0] == '_' && s[1] == '\0') || s[0] == '?')
		return ;
	i = ft_strchr_int(s, '=');
	if (!(s1 = ft_substr(s, 0, i)))
		errno = ENOMEM;
	if (!(s2 = ft_substr(s, i + 1, ft_strlen(s))))
	{
		free(s1);
		errno = ENOMEM;
	}
	if (errno)
		return ;
	print_declare_x(s1, s2);
	free(s1);
	free(s2);
}

void			export_sort_print(char **env)
{
	t_list		*tl;
	int			size;

	tl = copy_env_to_tlist(env);
	size = ft_lstsize(tl);
	sorting_list_env(&tl, size);
	ft_lstiter(tl, print_export_woo);
	ft_lstclear(&tl, del_content);
}
