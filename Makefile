# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/03 14:37:18 by vsaltel           #+#    #+#              #
#    Updated: 2019/04/12 16:59:05 by frossiny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
#CFLAGS	+=	-Wall -Werror -Wextra -g3
CFLAGS	+= -g3 -fsanitize=address

SHELL	=	bash

NAME 	=	21sh
LIBFT	=	libft
SRCDIR	=	srcs
INCDIR	=	includes
OBJDIR	=	objs
FILES 	=	main.c						\
			minishell.c					\
			termcaps/read_input.c		\
			termcaps/termcaps.c			\
			termcaps/initialization.c	\
			termcaps/set_position.c		\
			termcaps/t_up.c				\
			termcaps/t_down.c			\
			termcaps/t_history_next.c	\
			termcaps/t_history_prev.c	\
			termcaps/t_left_word.c		\
			termcaps/t_right_word.c		\
			termcaps/t_left.c			\
			termcaps/t_right.c			\
			termcaps/t_delete.c			\
			termcaps/t_home.c			\
			termcaps/t_end.c			\
			termcaps/history.c			\
			lexer/lexer.c				\
			lexer/is_escaped.c			\
			lexer/is_word_token.c		\
			lexer/lexer_free.c			\
			lexer/lexer_search.c		\
			lexer/create_token.c		\
			lexer/push_token.c			\
			lexer/parse_error.c			\
			lexer/states/general.c		\
			lexer/states/quotes.c		\
			lexer/states/comment.c		\
			lexer/states/escaped.c		\
			lexer/states/operators.c	\
			parser/parser.c				\
			parser/pipe.c				\
			parser/pipeline.c			\
			parser/redirections.c		\
			parser/executables.c		\
			ast/build_ast.c				\
			ast/create_node.c			\
			ast/build_args.c			\
			ast/redirections.c			\
			ast/destroy_ast.c			\
			exec_utils.c				\
			env/build_env.c				\
			env/copy_env.c				\
			env/count_env.c				\
			env/disp_env.c				\
			env/disp_free_env.c			\
			env/free_env.c				\
			env/get_enve.c				\
			env/new_envl.c				\
			builtins.c					\
			builtins_errors.c			\
			builtins/env.c				\
			builtins/setenv.c			\
			builtins/unsetenv.c			\
			builtins/exit.c				\
			builtins/cd.c				\
			builtins/echo.c				\
			utils/dup_argv.c			\
			utils/get_var_size.c		\
			signals.c					\
			errors.c					\
			utils.c						\
			variables.c					\
			tilde.c
SRCS	=	$(addprefix $(SRCDIR)/, $(FILES))
OBJS 	=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

##### Colors #####
_END=\x1b[0m
_BOLD=\x1b[1m
_UNDER=\x1b[4m
_REV=\x1b[7m
_GREY=\x1b[30m
_RED=\x1b[31m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_BLUE=\x1b[34m
_PURPLE=\x1b[35m
_CYAN=\x1b[36m
_WHITE=\x1b[37m

.PHONY: all clean fclean re $(LIBFT)

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -q -C $(LIBFT) || $(MAKE) -C $(LIBFT)
	@echo -e -n "\n${_BLUE}${_BOLD}[Create Executable] $(NAME)${_END}"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L./$(LIBFT) -lft -ltermcap
	@echo -e "\n${_GREEN}${_BOLD}$(NAME) done.${_END}"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
	@[ -d $(OBJDIR)/ast ] || mkdir -p $(OBJDIR)/ast
	@[ -d $(OBJDIR)/builtins ] || mkdir -p $(OBJDIR)/builtins
	@[ -d $(OBJDIR)/env ] || mkdir -p $(OBJDIR)/env
	@[ -d $(OBJDIR)/lexer ] || mkdir -p $(OBJDIR)/lexer
	@[ -d $(OBJDIR)/lexer/states ] || mkdir -p $(OBJDIR)/lexer/states
	@[ -d $(OBJDIR)/parser ] || mkdir -p $(OBJDIR)/parser
	@[ -d $(OBJDIR)/termcaps ] || mkdir -p $(OBJDIR)/termcaps
	@[ -d $(OBJDIR)/utils ] || mkdir -p $(OBJDIR)/utils
	@echo -n -e "\r\033[K${_PURPLE}${BOLD}[${NAME}] Compiling $<${_END}"
	@$(CC) $(CFLAGS) -I $(INCDIR) -I $(LIBFT)/$(INCDIR) -o $@ -c $<

clean:
	@$(MAKE) -C $(LIBFT) clean
	@echo -e "${_RED}${_BOLD}Cleaning obj files...${_END}"
	@rm -f $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean
	@echo -e "${_RED}${_BOLD}Cleaning project...${_END}"
	@rm -f $(NAME)

re: fclean
	@$(MAKE)
