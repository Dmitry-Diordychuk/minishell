# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/06 16:34:49 by kdustin           #+#    #+#              #
#    Updated: 2020/09/20 02:28:27 by kdustin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

REG_OBJS =	ft_memset.o				\
			ft_bzero.o				\
			ft_memcpy.o				\
			ft_memccpy.o			\
			ft_memmove.o			\
			ft_memchr.o				\
			ft_memcmp.o				\
			ft_strlen.o				\
			ft_strlcpy.o			\
			ft_strlcat.o			\
			ft_strchr.o				\
			ft_strrchr.o			\
			ft_strnstr.o			\
			ft_strncmp.o			\
			ft_atoi.o				\
			ft_isalpha.o			\
			ft_isdigit.o			\
			ft_isalnum.o			\
			ft_isascii.o			\
			ft_isprint.o			\
			ft_toupper.o			\
			ft_tolower.o			\
			ft_calloc.o				\
			ft_strdup.o				\
			ft_substr.o				\
			ft_strjoin.o			\
			ft_strtrim.o			\
			ft_split.o				\
			ft_itoa.o				\
			ft_strmapi.o			\
			ft_putchar_fd.o			\
			ft_putstr_fd.o			\
			ft_putendl_fd.o			\
			ft_putnbr_fd.o			\
			ft_strpbrk.o			\
			ft_strcmp.o				\
			ft_malloc.o				\
			ft_free.o				\
			ft_putunbr_fd.o			\
			ft_strrotate.o			\
			ft_strcpy.o				\
			get_next_line.o			\
			get_next_line_utils.o	\
			ft_isspace.o			\
			ft_atof.o

BONUS_OBJS =	ft_lstnew.o			\
				ft_lstadd_front.o	\
				ft_lstsize.o		\
				ft_lstlast.o		\
				ft_lstadd_back.o	\
				ft_lstdelone.o		\
				ft_lstclear.o		\
				ft_lstiter.o		\
				ft_lstmap.o			\
				ft_lstfind.o		\
				ft_lstget.o			\
				ft_lstpush.o

ifdef WITH_BONUS
OBJ_FILES =	$(REG_OBJS) $(BONUS_OBJS)
else
OBJ_FILES = $(REG_OBJS)
endif

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar rc $@ $^

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(REG_OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

bonus:
	$(MAKE) WITH_BONUS=1 all

.PHONY: all clean fclean re bonus

so:
	gcc $(FLAGS) -fPIC -c *.c
	gcc -shared -o libft.so *.o
