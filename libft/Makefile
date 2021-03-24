# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/06 16:34:49 by kdustin           #+#    #+#              #
#    Updated: 2021/03/24 22:02:57 by kdustin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS =		ft_memset.o					\
			ft_bzero.o					\
			ft_memcpy.o					\
			ft_memccpy.o				\
			ft_memmove.o				\
			ft_memchr.o					\
			ft_memcmp.o					\
			ft_strlen.o					\
			ft_strlcpy.o				\
			ft_strlcat.o				\
			ft_strchr.o					\
			ft_strrchr.o				\
			ft_strnstr.o				\
			ft_strncmp.o				\
			ft_atoi.o					\
			ft_isalpha.o				\
			ft_isdigit.o				\
			ft_isalnum.o				\
			ft_isascii.o				\
			ft_isprint.o				\
			ft_isset.o					\
			ft_toupper.o				\
			ft_tolower.o				\
			ft_calloc.o					\
			ft_strdup.o					\
			ft_strdup_between.o			\
			ft_substr.o					\
			ft_strjoin.o				\
			ft_strtrim.o				\
			ft_strtrim_head.o			\
			ft_strtrim_tail.o			\
			ft_split.o					\
			ft_itoa.o					\
			ft_strmapi.o				\
			ft_putchar_fd.o				\
			ft_putstr_fd.o				\
			ft_putendl_fd.o				\
			ft_putnbr_fd.o				\
			ft_strpbrk.o				\
			ft_strcmp.o					\
			ft_malloc.o					\
			ft_free.o					\
			ft_putunbr_fd.o				\
			ft_strrotate.o				\
			ft_strcpy.o					\
			get_next_line.o				\
			get_next_line_utils.o		\
			ft_isspace.o				\
			ft_atof.o					\
			ft_lstnew.o					\
			ft_lstadd_front.o			\
			ft_lstsize.o				\
			ft_lstlast.o				\
			ft_lstadd_back.o			\
			ft_lstdelone.o				\
			ft_lstclear.o				\
			ft_lstiter.o				\
			ft_lstmap.o					\
			ft_lstfind.o				\
			ft_lstget.o					\
			ft_lstpush.o				\
			ft_dlst_new.o				\
			ft_dlst_del.o				\
			ft_dlst_clear.o				\
			ft_dlst_append.o			\
			ft_dlst_prepend.o			\
			ft_dlst_insert.o			\
			ft_dlst_getfirst_data.o		\
			ft_dlst_getfirst_elem.o		\
			ft_dlst_getlast_data.o		\
			ft_dlst_getlast_elem.o		\
			ft_dlst_getnth_data.o		\
			ft_dlst_getnth_elem.o		\
			ft_dlst_size.o				\
			ft_dlst_unlink_elem.o		\
			ft_dlst_sort.o				\
			ft_dlst_find.o				\
			ft_diter_init.o				\
			ft_diter_more.o				\
			ft_diter_getnext.o			\
			ft_diter_remove.o			\
			ft_dlst_popfirst_data.o		\
			ft_dlst_popfirst_elem.o		\
			ft_dlst_poplast_data.o		\
			ft_dlst_poplast_elem.o		\
			ft_dlst_popnth_data.o		\
			ft_dlst_popnth_elem.o		\
			ft_dlst_removefirst.o		\
			ft_dlst_removelast.o		\
			ft_dlst_removenth.o			\
			ft_dlst_dup.o				\
			ft_strtok.o					\
			ft_putchar.o

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $@ $^

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re

so:
	gcc $(FLAGS) -fPIC -c *.c
	gcc -shared -o libft.so *.o
