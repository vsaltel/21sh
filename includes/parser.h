/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:50:15 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/08 14:55:54 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "shell.h"

typedef struct		e_redirect
{
	int				append : 1;
	int				filedes;
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
	struct e_anode	*left;
	struct e_anode	*right;
}					t_anode;

int					parse(t_lexer *lexer, t_env **env);

int					build_args(char ***args, t_token *tokens);
t_anode				*create_node(t_token *ope, t_cmd *cmd);

char				*trim_quotes(char *str);

#endif