/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 15:32:14 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/12 19:37:16 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

int		get_next_line(int fd, char **line);
char	*strchr(const char *s, int c);
size_t	strlen(const char *str);
size_t	strlcat(char *dst, const char *src, size_t size);
char	*data_add(char *data, const char *buf, int actl_buf_len);
char	*strdup(const char *s1);
char	*cut_first_line(char **data);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# if BUFFER_SIZE < 1
#  error wrong BUFFER_SIZE
# elif BUFFER_SIZE > SIZE_MAX
#  error wrong BUFFER_SIZE
# endif

#endif
