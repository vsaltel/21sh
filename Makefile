# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/03 14:37:18 by vsaltel           #+#    #+#              #
#    Updated: 2019/05/07 16:37:08 by frossiny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc -g3
#CFLAGS	+=	-Wall -Werror -Wextra -g3
#CFLAGS	+= -g3 -fsanitize=address

SHELL	=	bash

NAME 	=	21sh
LIBFT	=	libft
SRCDIR	=	srcs
INCDIR	=	includes
OBJDIR	=	objs
FILES 	=	main.c									\
			shell.c									\
			prompt.c								\
			termcaps/read_input.c					\
			termcaps/termcaps.c						\
			termcaps/initialization.c				\
			termcaps/set_position.c					\
			termcaps/set_position_utils.c			\
			termcaps/completion/t_completion.c		\
			termcaps/completion/files.c				\
			termcaps/completion/path.c				\
			termcaps/t_up.c							\
			termcaps/t_down.c						\
			termcaps/t_history_next.c				\
			termcaps/t_history_prev.c				\
			termcaps/t_history_search.c				\
			termcaps/t_left_word.c					\
			termcaps/t_right_word.c					\
			termcaps/t_left.c						\
			termcaps/t_right.c						\
			termcaps/t_delete.c						\
			termcaps/t_delete_right.c				\
			termcaps/t_home.c						\
			termcaps/t_end.c						\
			termcaps/t_visual_mode.c				\
			termcaps/t_visual_cut.c					\
			termcaps/t_visual_paste.c				\
			termcaps/t_visual_copy.c				\
			termcaps/history.c						\
			termcaps/history_utils.c				\
			termcaps/signal.c						\
			lexer/lexer.c							\
			lexer/is_escaped.c						\
			lexer/is_word_token.c					\
			lexer/lexer_free.c						\
			lexer/lexer_search.c					\
			lexer/create_token.c					\
			lexer/push_token.c						\
			lexer/parse_error.c						\
			lexer/states/general.c					\
			lexer/states/quotes.c					\
			lexer/states/comment.c					\
			lexer/states/escaped.c					\
			lexer/states/operators.c				\
			parser/parser.c							\
			parser/pipe.c							\
			parser/pipeline.c						\
			parser/redirections.c					\
			parser/executables.c					\
			parser/here_doc.c						\
			parser/hashtable/ht_create.c			\
			parser/hashtable/ht_hash.c				\
			parser/hashtable/ht_delone.c			\
			parser/hashtable/ht_delete.c			\
			parser/hashtable/ht_put.c				\
			parser/hashtable/ht_get.c				\
			parser/hashtable/ht_exists.c			\
			parser/exec_utils.c						\
			ast/build_ast.c							\
			ast/create_node.c						\
			ast/build_args.c						\
			ast/redirections.c						\
			ast/destroy_ast.c						\
			ast/create_cmd.c						\
			env/build_env.c							\
			env/copy_env.c							\
			env/count_env.c							\
			env/disp_env.c							\
			env/disp_free_env.c						\
			env/free_env.c							\
			env/get_enve.c							\
			env/new_envl.c							\
			env/dup_env.c							\
			builtins/builtins.c						\
			builtins/builtins_errors.c				\
			builtins/env.c							\
			builtins/setenv.c						\
			builtins/unsetenv.c						\
			builtins/exit.c							\
			builtins/cd.c							\
			builtins/echo.c							\
			utils/dup_argv.c						\
			utils/get_var_size.c					\
			signals.c								\
			errors.c								\
			utils.c									\
			variables.c								\
			tilde.c
SRCS	=	$(addprefix $(SRCDIR)/, $(FILES))
OBJS 	=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJSD 	=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.d)

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

.PHONY: all clean fclean re norm $(LIBFT)

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
	@[ -d $(OBJDIR)/parser/hashtable ] || mkdir -p $(OBJDIR)/parser/hashtable
	@[ -d $(OBJDIR)/termcaps ] || mkdir -p $(OBJDIR)/termcaps
	@[ -d $(OBJDIR)/termcaps/completion ] || mkdir -p $(OBJDIR)/termcaps/completion
	@[ -d $(OBJDIR)/utils ] || mkdir -p $(OBJDIR)/utils
	@echo -n -e "\r\033[K${_PURPLE}${BOLD}[${NAME}] Compiling $<${_END}"
	@$(CC) $(CFLAGS) -I $(INCDIR) -I $(LIBFT)/$(INCDIR) -MMD -o $@ -c $<

clean:
	@$(MAKE) -C $(LIBFT) clean
	@echo -e "${_RED}${_BOLD}Cleaning obj files...${_END}"
	@rm -f $(OBJS)
	@rm -f $(OBJSD)

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean
	@echo -e "${_RED}${_BOLD}Cleaning project...${_END}"
	@rm -f $(NAME)

re: fclean
	@$(MAKE)

norm:
	@norminette $(INCDIR) $(SRCDIR) | grep "Warning\|Error" || true
	@echo "Norm done!"

-include $(OBJSD)
