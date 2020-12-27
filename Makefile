# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/16 13:35:35 by kdustin           #+#    #+#              #
#    Updated: 2020/12/26 20:20:08 by kdustin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR := sources
SRC_SUB_DIR := buildin environment error execute lexer parser signal tests
OBJ_DIR := objects
BIN_DIR := .
INC_DIR := includes

NAME := $(BIN_DIR)/minishell
LIBFT_DIR := libft

LDFLAGS := -L$(LIBFT_DIR)
LDLIBS := -lft

CFLAGS := -g #-Wall -Werror -Wextra

SRCS_BUILDIN := $(addprefix buildin/,		cd.c		\
											echo.c		\
											env.c		\
											exit.c		\
											export.c	\
											ls.c		\
											pwd.c		\
											unset.c)

SRCS_ENVIRONMENT := $(addprefix buildin/,	environment.c)

SRCS_ERROR := $(addprefix error/,			error.c)

SRCS_EXECUTE := $(addprefix execute/,		command.c 			\
											execute_utils.c		\
											simple_command.c)

SRCS_LEXER := $(addprefix lexer/,			lexer_utils.c		\
											lexer.c				\
											token.c)

SRCS_PARSER := $(addprefix parser/,			parser.c)
SRCS_SIGNAL := $(addprefix signal/, )
SRCS_TESTS := $(addprefix tests/,			simple_command_test.c \
											lexer_parser_test.c)

SRCS := $(addprefix $(SRC_DIR)/,	$(SRCS_BUILDIN)		\
									$(SRCS_ENVIRONMENT)	\
									$(SRCS_ERROR)		\
									$(SRCS_EXECUTE)		\
									$(SRCS_LEXER)		\
									$(SRCS_PARSER)		\
									$(SRCS_SIGNAL)		\
									main.c)

SRCS_TEST := SRCS $(addprefix $(SRC_DIR)/, $(SRCS_TESTS))

OBJS := $(addprefix $(OBJ_DIR)/, $(notdir $(patsubst %.c, %.o, $(SRCS))))
OBJS_TEST := $(addprefix $(OBJ_DIR)/, $(notdir $(patsubst %.c, %.o, $(SRCS_TESTS))))

all: $(NAME)

$(NAME): $(OBJS) | $(BIN_DIR)
	$(MAKE) -C $(LIBFT_DIR)/ bonus
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

vpath %.c $(SRC_DIR) $(addprefix $(SRC_DIR)/, $(SRC_SUB_DIR))

$(OBJ_DIR)/%.o: %.c $(INC_DIR)/minishell.h | $(OBJ_DIR)
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

simple_command_test: objects/simple_command_test.o objects/simple_command.o objects/execute_utils.o
	$(MAKE) -C $(LIBFT_DIR)/ bonus
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o simple_command_test

lexer_parser_test: objects/lexer_parser_test.o objects/lexer.o objects/token.o objects/lexer_utils.o objects/parser.o objects/environment.o objects/command.o objects/simple_command.o objects/execute_utils.o
	$(MAKE) -C $(LIBFT_DIR)/ bonus
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o lexer_parser_test
