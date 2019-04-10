/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:50:15 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/10 20:34:44 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "shell.h"

typedef struct		e_redirect
{
	int					done : 1;
	int					append : 1;
	int					filedes;
	t_token_type		type;
	t_token				*value;
	struct e_redirect	*next;
}					t_redirect;

typedef struct 		e_cmd
{
	t_token			*exe;
	char			**args;
	int				argc;
	t_redirect		*redir;
}					t_cmd;

typedef struct		e_anode
{
	t_token			*ope;
	t_cmd			*cmd;
	struct e_anode	*parent;
	struct e_anode	*left;
	struct e_anode	*right;
}					t_anode;

int					build_ast(t_lexer *lexer, t_anode **ast, t_env **env);

int					build_args(char ***args, t_token *tokens);
t_anode				*create_node(t_token *ope, t_cmd *cmd);
t_redirect			*parse_redirections(t_token *tok, int offset);
t_cmd				*create_cmd(t_token *exe);

#endif