# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/16 13:35:35 by kdustin           #+#    #+#              #
#    Updated: 2020/12/16 16:33:10 by kdustin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR := sources
SRC_SUB_DIR := buildin execute parser signal
OBJ_DIR := objects
BIN_DIR := .

NAME := $(BIN_DIR)/minishell

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
	$(CC) $^ -o $@

vpath %.c $(SRC_DIR) $(addprefix $(SRC_DIR)/, $(SRC_SUB_DIR))

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) -rv $(OBJ_DIR)

fclean: clean
	$(RM) -rv $(NAME)

re: fclean all

.PHONY: all clean fclean re