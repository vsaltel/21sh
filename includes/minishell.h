/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:59:10 by frossiny          #+#    #+#             */
/*   Updated: 2019/03/28 19:11:36 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <curses.h>
#include <term.h>
#include <termios.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "lexer.h"
# include "termcaps.h"

#define BUFF 64

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

extern int			g_child;
extern int			g_ignore_signals;
extern int			g_return;

int					minishell(t_env **env);
int					check_quotes(char *str, char c);

t_env				*copy_env(char **envp, int inc);
int					disp_env(t_env *env);
t_env				*get_enve(t_env *env, char *key);
t_env				*new_envl(t_env **env, char *key, char *value, int inc);
int					delete_env(t_env **env, char *key);
char				**build_env(t_env *env);
void				free_env(t_env **env);
int					disp_free_env(t_env **env);
char				**dup_argv(int argc, char **args, char ***argv);

int					lex(char *s, t_lexer *lexer);
int					is_escaped(char *s, size_t index, int endquote);
int					is_start_quote(char *s, size_t index);
void				destroy_lexer(t_lexer *lexer);
t_token				*push_token(t_token *list, t_token *new);
t_token				*create_token(t_lexer *lexer, char *content,
									size_t len, t_token_type type);
t_ex_token			search_token(const char *s);
void				destroy_tokens(t_token *token);
int					replace_vars(t_token *curr, t_env *env);
size_t				get_var_size(char *key);
int					handle_home(t_token *token, t_env *env);

int					parse(t_lexer *lexer, t_env **env);
char				*get_exe(t_env *env, char *name, int verbose);
int					execute(char *file, char ***args, t_env **env,
																t_lexer *lex);
int					handle_builtin(char *name, char ***argv, t_env **env,
																t_lexer *lex);
int					is_builtin(char *name);
int					b_env(int argc, char ***argv, t_env **env, t_lexer *lex);
int					b_setenv(int argc, char ***argv, t_env **env, t_lexer *lex);
int					b_unsetenv(int argc, char ***argv, t_env **env,
																t_lexer *lex);
int					b_exit(int argc, char ***argv, t_env **env, t_lexer *lex);
int					b_cd(int argc, char ***argv, t_env **env, t_lexer *lex);
int					b_echo(int argc, char ***argv, t_env **env, t_lexer *lex);

void				register_signals(void);

int					is_local_exe(char *name);
int					is_relative_path(char *name);
char				*format_path_exe(char *dir, char *file);
int					cd_is_dir(char *file, char *name);

void				inexistant(char *name);
void				not_found(char *name);
void				permission_denied(char *name);
void				no_user(char *name);
int					cd_exists(char *file, char *name);
void				env_invalid_arg(int *argc, char ***argv);

int					get_input(int fd, char **dest);
int					execute_termcaps(char *buf, char **str, t_cursor_pos *pos);
int					my_putchar(int c);
#endif
