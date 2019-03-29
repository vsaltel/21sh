# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/03 14:37:18 by vsaltel           #+#    #+#              #
#    Updated: 2019/03/28 19:34:46 by vsaltel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
#CFLAGS	+=	-Wall -Werror -Wextra -g3
CFLAGS	+= -g -fsanitize=address

NAME 	=	21sh
LIBFT	=	libft
SRCDIR	=	srcs
INCDIR	=	includes
OBJDIR	=	objs
FILES 	=	main.c				\
			minishell.c			\
			read_input.c		\
			termcaps.c			\
			lexer.c				\
			lexer_utils.c		\
			tokens_utils.c		\
			parser.c			\
			executables.c		\
			exec_utils.c		\
			env_utils.c			\
			env_utilities.c		\
			builtins.c			\
			builtins_errors.c	\
			builtins/env.c		\
			builtins/setenv.c	\
			builtins/unsetenv.c	\
			builtins/exit.c		\
			builtins/cd.c		\
			builtins/echo.c		\
			signals.c			\
			errors.c			\
			utils.c				\
			variables.c			\
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
	@echo "${_BLUE}${_BOLD}[Create Executable] $(NAME)${_END}"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L./$(LIBFT) -lft -ltermcap
	@echo "${_GREEN}${_BOLD}$(NAME) done.${_END}"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
	@[ -d $(OBJDIR)/builtins ] || mkdir -p $(OBJDIR)/builtins
	@echo "${_PURPLE}${BOLD}[${NAME}] Compiling $<${_END}"
	@$(CC) $(CFLAGS) -I $(INCDIR) -I $(LIBFT)/$(INCDIR) -o $@ -c $<

clean:
	@$(MAKE) -C $(LIBFT) clean
	@echo "${_RED}${_BOLD}Cleaning obj files...${_END}"
	@rm -f $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean
	@echo "${_RED}${_BOLD}Cleaning project...${_END}"
	@rm -f $(NAME)

re: fclean
	@$(MAKE)
