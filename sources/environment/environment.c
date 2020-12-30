/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 22:27:20 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/29 17:15:37 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var *create_env_var(char *name, char *value)
{
	t_env_var *new_var;

	if (!(new_var = (t_env_var*)malloc(sizeof(t_env_var))))
		return (NULL);
	new_var->name = name;
	new_var->value = value;
	return (new_var);
}

int add_env_var(t_list **env_vars, char *name, char *value)
{
	t_env_var	*new_var;
	t_list		*new_elem;

	if (!(new_var = create_env_var(name, value)))
		return (ALLOCATION_FAILED);
	if (!(new_elem = ft_lstnew((void*)new_var)))
	{
		free(new_var);
		return (ALLOCATION_FAILED);
	}
	ft_lstpush(env_vars, new_elem);
	return (SUCCESSED);
}

int env_var_cmp(void *a, void *b)
{
	return (ft_strcmp((char*)a, ((t_env_var*)b)->name));
}

char *find_env_var(t_list *env_vars, char *name)
{
	t_env_var	*var;
	t_list		*tmp;

	tmp = ft_lstfind(env_vars, name, env_var_cmp);
	if (tmp == NULL)
		return (NULL);
	var = (t_env_var*)(tmp->content);
	return (var->value);
}

void *env_free_handler(char **res, char *tmp, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		free(res[i]);
	}
	free(res);
	free(tmp);
	return (NULL);
}

char **list_to_array(t_list *list)
{
	t_env_var	*env;
	char		*tmp;
	char		*str;
	char		**res;
	int			i;

	i = 0;
	tmp = NULL;
	if (!(res = (char**)calloc(sizeof(char*), (ft_lstsize(list) + 1))))
	while (list != NULL)
	{
		env = (t_env_var*)list->content;
		if (!(tmp = ft_strjoin(env->name, "=")))
			return (env_free_handler(res, tmp, i));
		if (!(str = ft_strjoin(tmp, env->value)))
			return (env_free_handler(res, tmp, i));
		free(tmp);
		res[i] = str;
		list = list->next;
		i++;
	}
	return (res);
}
