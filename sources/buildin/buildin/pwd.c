/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: che <che@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 05:26:01 by kdustin           #+#    #+#             */
/*   Updated: 2021/01/01 23:06:44 by che              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <errno.h>

int		ft_pwd(char **args)
{
	char    pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
    {
        if(errno == ERANGE)
            ft_putstr_fd("ERANGE", 1);
        if(errno == ENODEV)
            ft_putstr_fd("ENODEV", 1);
        if(errno == ENOMEM)
            ft_putstr_fd("ENOMEM", 1);
        return (1);
    }
// При ошибке функция getcwd() возвращает значение NULL,
// а переменная errno устанавливается равной ENODEV (устройство не существует),
// ENOMEM (недостаточно памяти) или ERANGE (ошибка области).
    else
    {
        ft_putstr_fd(pwd, 1);
        ft_putstr_fd("\n", 1);
        return (0);    
    }
}