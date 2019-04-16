/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:17:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/12 16:05:45 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_cmd			*create_cmd(t_token *exe)
{
	t_cmd	*cmd;
	char	**argv;

	if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->exe = exe;
	cmd->argc = -1;
	cmd->args = NULL;
	cmd->redir = NULL;
	return (cmd);
}

static int		parse_tree(t_token *tokens, t_anode **ast)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE || tokens->type == TOKEN_AND
											|| tokens->type == TOKEN_OR)
		{
			if (!*ast)
				return (0);
			tokens = create_ope_node(ast, tokens);
		}
		else if (is_word_token(tokens))
			tokens = create_cmd_node(ast, tokens);
		else if (tokens->type == TOKEN_SEMI)
			tokens = tokens->next;
		else
			break ;
	}
	return (1);
}

int				build_ast(t_shell *shell, t_anode **ast)
{
	return (parse_tree(shell->lexer.tokens, ast));
}
