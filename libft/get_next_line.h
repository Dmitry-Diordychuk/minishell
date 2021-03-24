/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 15:32:14 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/24 22:05:17 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <term.h>

int		get_next_line(int fd, char **line);
char	*strchr(const char *s, int c);
size_t	strlen(const char *str);
size_t	strlcat(char *dst, const char *src, size_t size);
char	*data_add(char *data, const char *buf, int actl_buf_len);
char	*strdup(const char *s1);
char	*cut_first_line(char **data);

# define BUFFER_SIZE 256
#endif
