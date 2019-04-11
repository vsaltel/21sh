/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:59:10 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/11 18:32:17 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <curses.h>
# include <term.h>
# include <termios.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "lexer.h"
# include "ast.h"
# include "parser.h"
# include "termcaps.h"
# include "builtins.h"

typedef struct		s_env
{
	char			*key;
	char			*value;
	int				is_env;
	struct s_env	*next;
}					t_env;

typedef struct		s_shell
{
	int				ret;
	t_env			*env;
	t_lexer			lexer;
	t_anode			*ast;
}					t_shell;

# define BUFF 64

extern int			g_child;
extern int			g_ignore_signals;
extern int			g_return;

int					minishell(t_shell *shell);
int					check_quotes(char *str, char c);

int					lex(char *s, t_lexer *lexer);
int					is_escaped(char *s, size_t index, int endquote);
t_ex_token			lexer_search(const char *s);
void				destroy_lexer(t_lexer *lexer);
t_token				*push_token(t_token *list, t_token *new);
t_token				*create_token(t_lexer *lexer, char *content,
								size_t len, t_token_type type);
void				destroy_tokens(t_token *token);
int					is_word_token(t_token *token);

int					build_ast(t_shell *shell, t_anode **ast);
int					build_args(t_cmd *cmd, t_shell *shell);
t_anode				*create_node(t_token *ope, t_cmd *cmd);
t_token				*create_ope_node(t_anode **tree, t_token *tokens);
t_token				*create_cmd_node(t_anode **tree, t_token *tokens);
t_cmd				*create_cmd(t_token *exe);
void				destroy_ast(t_shell *shell);

int					parse(t_shell *shell, t_anode *ast);
int					execute_pipes(t_anode *node, t_shell *shell, t_anode **cn);
t_pipel				*build_pipeline(t_anode *node, t_shell *shell, t_anode **cn);
t_redirect			*parse_redirections(t_token *tok, int offset);
void				del_pipeline(t_pipel *pline);

t_env				*copy_env(char **envp, int inc);
int					disp_env(t_env *env);
t_env				*get_enve(t_env *env, char *key);
t_env				*new_envl(t_env **env, char *key, char *value, int inc);
int					delete_env(t_env **env, char *key);
char				**build_env(t_env *env);
void				free_env(t_env **env);
int					disp_free_env(t_env **env);
size_t				count_env(t_env *env);
char				**dup_argv(int argc, char **args, char ***argv);

int					replace_vars(t_token *curr, t_shell *shell);
size_t				get_var_size(char *key);
int					handle_home(t_token *token, t_env *env);

char				*get_exe(t_env *env, char *name, int verbose);
int					is_exe(t_env *env, char *name, int verbose);
int					execute(t_cmd *cmd, t_shell *shell);
int					handle_builtin(t_cmd *cmd, t_shell *shell);
int					is_builtin(char *name);
int					b_env(t_cmd *cmd, t_shell *shell);
int					b_setenv(t_cmd *cmd, t_shell *shell);
int					b_unsetenv(t_cmd *cmd, t_shell *shell);
int					b_exit(t_cmd *cmd, t_shell *shell);
int					b_cd(t_cmd *cmd, t_shell *shell);
int					b_echo(t_cmd *cmd, t_shell *shell);

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
void				new_entry(char **str, char *buf, t_cursor_pos *pos);
void				del_char(char **str, t_cursor_pos *pos);
void				final_position(t_cursor_pos *pos);
int					my_putchar(int c);

#endif
