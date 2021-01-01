/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 15:28:44 by kdustin           #+#    #+#             */
/*   Updated: 2021/01/01 16:09:01 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	handle_error(char **str)
{
	if (*str)
		free(*str);
	return (-1);
}

int			get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE];
	static char	*data;
	int			counter;

	buf[0] = '\0';
	counter = 1;
	while (!strchr(data, '\n') && (counter = read(fd, buf, BUFFER_SIZE)) >= 0)
	{
		if (counter == 0)
			write(1, "  \b\b", 4);
		if (data == NULL && counter == 0)
			break;
		if (!(data = data_add(data, buf, counter)))
			return (handle_error(&data));
	}
	if (counter < 0)
		return (handle_error(&data));
	if (!(*line = cut_first_line(&data)))
		return (handle_error(&data));
	if (counter == 0)
		return (0);
	return (1);
}
