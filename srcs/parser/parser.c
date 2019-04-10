/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:17:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/10 20:32:23 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	parse_condition(int *ret, t_anode *cond, t_env **env, t_lexer *lex)
{
	if (cond->ope->type == TOKEN_AND)
	{
		if (*ret != 0)
			return (0);
		*ret = execute(cond->right->cmd, env, lex);
		return (1);
	}
	else if (cond->ope->type == TOKEN_OR)
	{
		if (*ret == 0)
			return (0);
		*ret = execute(cond->right->cmd, env, lex);
		return (1);
	}
	else
		return (1);
}

int			parse(t_lexer *lexer, t_anode *ast, t_env **env)
{
	int		ret;
	int		pipe[2];

	pipe[0] = -1;
	pipe[1] = -1;
	ret = 0;
	ft_printf("----- PARSING -----\n");
	ft_printf("Tree start: %s\n", ast->ope ? ast->ope->content : ast->cmd->exe->content);
	while (ast->left)
		ast = ast->left;
	ft_printf("First cmd: |%s|\n", ast->cmd->exe->content);
	while (ast)
	{
		//ft_printf("Parsing %s - p: %p - ope: %p\n", ast->ope ? ast->ope->content : ast->cmd->exe->content, ast->parent, ast->ope);
		if (!ast->ope && (!ast->parent || (ast->parent->ope && ast->parent->ope->type != TOKEN_PIPE)))
			ret = execute(ast->cmd, env, lexer);
		else if (ast->parent && (ast->parent->ope && ast->parent->ope->type == TOKEN_PIPE))
		{
			ft_printf("----------- PIPES ----------\n");
			ret = execute_pipes(ast, env, lexer);
			while (ast->parent && ast->parent && ast->parent->ope->type == TOKEN_PIPE)
				ast = ast->parent;
			ft_printf("--------- PIPES END --------\n");
		}
		else
		{
			if (ast->ope && (ast->ope->type == TOKEN_AND || ast->ope->type == TOKEN_OR))
			{
				if (!parse_condition(&ret, ast, env, lexer))
					return (ret);
			}
			else
				ast->ope ? ft_printf("Should have executed: %s\n", ast->ope->content) : 0;
		}
		ast = ast->parent;
	}
	ft_printf("-----   END   -----\n");
	return (ret);
}
