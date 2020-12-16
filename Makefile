# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/16 13:35:35 by kdustin           #+#    #+#              #
#    Updated: 2020/12/16 17:17:07 by kdustin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR := sources
SRC_SUB_DIR := buildin execute parser signal
OBJ_DIR := objects
BIN_DIR := .
INC_DIR := includes

NAME := $(BIN_DIR)/minishell
LIBFT_DIR := libft
LDFLAGS := -Llibft
LDLIBS := -lft

CFLAGS := -Wall -Werror -Wextra


SRCS_BUILDIN := $(addprefix buildin/,	cd.c		\
										echo.c		\
										env.c		\
										exit.c 		\
										export.c 	\
										ls.c 		\
										pwd.c 		\
										unset.c)
SRCS_EXECUTE := $(addprefix execute/, )
SRCS_PARSER := $(addprefix parser/, )
SRCS_SIGNAL := $(addprefix signal/, )

SRCS := $(addprefix $(SRC_DIR)/,	$(SRCS_BUILDIN) \
									$(SRCS_EXECUTE) \
									$(SRCS_PARSER) 	\
									$(SRCS_SIGNAL) 	\
									main.c)

OBJS := $(addprefix $(OBJ_DIR)/, $(notdir $(patsubst %.c, %.o, $(SRCS))))

all: $(NAME)

$(NAME): $(OBJS) | $(BIN_DIR)
	$(MAKE) -C $(LIBFT_DIR)/
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

vpath %.c $(SRC_DIR) $(addprefix $(SRC_DIR)/, $(SRC_SUB_DIR))

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	$(MAKE) -C $(LIBFT_DIR)/ clean
	$(RM) -rv $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR)/ fclean
	$(RM) -rv $(NAME)

re: fclean all
	$(MAKE) -C $(LIBFT_DIR)/ re

.PHONY: all clean fclean re