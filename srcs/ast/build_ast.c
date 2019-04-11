/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:17:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/11 13:21:58 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_token	*get_cmd_end(t_token *tok)
{
	while (tok)
	{
		if (is_word_token(tok))
			tok = tok->next;
		else if (tok->type == TOKEN_REDIRO || tok->type == TOKEN_REDIRI)
			tok = tok->next;
		else
			break ;
	}
	return (tok);
}

t_cmd 			*create_cmd(t_token *exe)
{
	t_cmd	*cmd;
	char	**argv;

	if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->exe = exe;
	cmd->argc = build_args(&argv, exe);
	cmd->args = argv;
	cmd->redir = parse_redirections(exe, cmd->argc);
	return (cmd);
}

static int		parse_tree(t_token *tokens, t_anode **ast, t_env **env)
{
	t_anode	*tree;
	t_anode	*tmp;
	t_cmd	*cmd;
	t_token	*curr;
	
	//TODO REPLACE VARS
	tree = NULL;
	curr = tokens;
	while (tokens)
	{
		ft_printf("Token: %s\n", tokens->content);
		if (tokens->type == TOKEN_PIPE)
		{
			if (!tree)
				return (0);
			ft_printf("New PIPE Node on %s\n", tree->ope ? tree->ope->content : tree->cmd->exe->content);
			tmp = create_node(tokens, NULL);
			tmp->left = tree;
			tree->parent = tmp;
			ft_printf("New CMD node on %s: %s\n", tmp->ope->content, tokens->next->content);
			tmp->right = create_node(NULL, create_cmd(tokens->next));
			tmp->right->parent = tmp;
			tree = tmp;
			tokens = get_cmd_end(tokens->next);
			curr = tokens;
		}
		else if (tokens->type == TOKEN_AND || tokens->type == TOKEN_OR)
		{
			if (!tree)
				return (0);
			ft_printf("New CONDITION Node on %s\n", tree->ope ? tree->ope->content : tree->cmd->exe->content);
			tmp = create_node(tokens, NULL);
			tree->parent = tmp;
			tmp->left = tree;
			ft_printf("New CMD node on %s: %s\n", tmp->ope->content, tokens->next->content);
			tmp->right = create_node(NULL, create_cmd(tokens->next));
			tmp->right->parent = tmp;
			tree = tmp;
			tokens = get_cmd_end(tokens->next);
			curr = tokens;
		}
		else if (is_word_token(tokens))
		{
			cmd = create_cmd(curr);
			if (!tree)
			{
				ft_printf("First node: %s\n", cmd->exe->content);
				tree = create_node(NULL, cmd);
			}
			else
			{
				ft_printf("New CMD node on %s: %s\n", tree->ope ? tree->ope->content : tree->cmd->exe->content, cmd->exe->content);
				tmp = create_node(NULL, cmd);
				tree->parent = tmp;
				tmp->left = tree;
				tree = tmp;
				
			}
			tokens = get_cmd_end(tokens);
			curr = tokens;
		}
		else if (tokens->type == TOKEN_SEMI)
			curr = tokens = tokens->next;
		else
		{
			ft_printf("Unknown token: (%d) %s\n", tokens->type, tokens->content);
			break ;
		}
	}
	*ast = tree;
	return (1);
}

int				build_ast(t_lexer *lexer, t_anode **ast, t_env **env)
{
	t_token	*tokens;

	if (lexer->tokens && lexer->tokens->content && !ft_strcmp(lexer->tokens->content, "exit")) //TEMP
		exit(120);

	return (parse_tree(lexer->tokens, ast, env));
}
