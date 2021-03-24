# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/16 13:35:35 by kdustin           #+#    #+#              #
#    Updated: 2021/03/24 21:47:47 by kdustin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR := sources
SRC_SUB_DIR := buildin environment error execute lexer parser signal tests term\
				word hist
OBJ_DIR := objects
BIN_DIR := .
INC_DIR := includes

NAME := $(BIN_DIR)/minishell
LIBFT_DIR := libft

LDFLAGS := -L$(LIBFT_DIR)
LDLIBS := -lft -ltermcap

CFLAGS := -g -Wall -Werror -Wextra

SRCS_BUILDIN := $(addprefix buildin/,			cd.c		\
												echo.c		\
												env.c		\
												exit.c		\
												export.c	\
												pwd.c		\
												unset.c		\
												sort.c)

SRCS_ENVIRONMENT := $(addprefix environment/,	environment.c)

SRCS_ERROR := $(addprefix error/,				error.c)

SRCS_EXECUTE := $(addprefix execute/,			execute.c			\
												fd.c)

SRCS_LEXER := $(addprefix lexer/,				lexer_recognize.c		\
												lexer_recognize_utils.c	\
												lexer.c)

SRCS_PARSER := $(addprefix parser/,				parser.c			\
												parser_word.c		\
												parser_command.c)
SRCS_SIGNAL := $(addprefix signal/, )

SRCS_TERM := $(addprefix term/,					init.c					\
												keys_handlers.c			\
												keys_handlers_arrows.c	\
												readline.c)

SRCS_WORD := $(addprefix word/,					word.c					\
												word_utils.c)

SRCS_HIST := $(addprefix hist/,					hist.c					\
												hist_utils.c)

SRCS := $(addprefix $(SRC_DIR)/,	$(SRCS_BUILDIN)		\
									$(SRCS_ENVIRONMENT)	\
									$(SRCS_ERROR)		\
									$(SRCS_EXECUTE)		\
									$(SRCS_LEXER)		\
									$(SRCS_PARSER)		\
									$(SRCS_SIGNAL)		\
									$(SRCS_TERM)		\
									$(SRCS_WORD)		\
									$(SRCS_HIST)		\
									main.c				\
									cmdtbl.c			\
									simcmd.c			\
									array.c				\
									file.c				\
									path.c				\
									expansion.c			\
									signal.c			\
									hist.c)

OBJS := $(addprefix $(OBJ_DIR)/, $(notdir $(patsubst %.c, %.o, $(SRCS))))
OBJS_TEST := $(addprefix $(OBJ_DIR)/, $(notdir $(patsubst %.c, %.o, $(SRCS_TESTS))))

all: $(NAME)

$(NAME): $(OBJS) | $(BIN_DIR)
	$(MAKE) -C $(LIBFT_DIR)/
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
