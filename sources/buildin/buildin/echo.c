/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: che <che@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 05:23:04 by kdustin           #+#    #+#             */
/*   Updated: 2021/01/01 20:58:20 by che              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

int count_args(char **arg)
{
    int n;

    n = 0;
	while (arg[n])
		n++;
	return (n);
}

int check_flag(char **arg)
{
    int i;
    int flag;

    
    i = 1;
    flag = 0;
    while (arg[i] && ft_strcmp(arg[i], "-n") == 0)
    {
        flag = 1;
        i++;
    }
    return(flag);
}

int ft_echo (char **arg)
{
    int i;
    int flag;
    int arg_size;

    i = 1;
    arg_size = count_args(arg);
    flag = check_flag(arg);
    if(flag)
        i++;
    if(arg_size < 2 && flag == 0)
        write(1, "\n", 1);
    if (arg_size)
    {
        while (arg[i])
        {
            ft_putstr_fd(arg[i], 1);
            i++;
            if(arg[i] != NULL && i < arg_size)
                write(1, " ", 1);
            if(arg[i] == NULL && flag == 0)
                write(1, "\n", 1);
        } 
    }
    return (0);
}
