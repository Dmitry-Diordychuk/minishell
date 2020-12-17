/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 05:28:29 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/17 15:16:34 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void error(char *message)
{
	ft_putstr_fd("Error: ", 1);
	ft_putstr_fd(message, 1);
	exit(EXIT_FAILURE);
}


