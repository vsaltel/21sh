/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:17:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/03 12:21:01 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	build_args(char ***args, t_token *tokens)
{
	int		argc;
	int		i;
	t_token	*tmp;

	argc = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type != TOKEN_NAME && tmp->type != TOKEN_QUOTES
				&& tmp->type != TOKEN_DQUOTES)
			break ;
		argc++;
		tmp = tmp->next;
	}
	if (!((*args) = (char **)malloc(sizeof(char *) * (argc + 1))))
		exit(-1);
	tmp = tokens;
	i = 0;
	while (tmp && i < argc)
	{
		(*args)[i++] = tmp->content;
		tmp = tmp->next;
	}
	(*args)[i] = NULL;
	return (argc);
}

static void	end_parse(t_token **tokens, int argc, char ***args)
{
	*tokens = (*tokens)->next;
	while (*tokens && --argc)
		*tokens = (*tokens)->next;
	if (args && *args)
		free(*args);
	*args = NULL;
}

static int	handle_operator(t_token *start, t_token **current, int *ret)
{
	t_token *tokens;

	tokens = *current;
	if (tokens->type < 4)
		return (1);
	else if (tokens->type == TOKEN_SEMI)
		while (tokens && tokens->type == TOKEN_SEMI)
			tokens = tokens->next;
	else if (tokens == start)
	{
		*ret = 1;
		return (0);
	}
	else
	{
		if (tokens->type == TOKEN_AND && *ret)
			return (0);
		else if (tokens->type == TOKEN_OR && !*ret)
			return (0);
		while (tokens && tokens->type > 3)
			tokens = tokens->next;
	}
	*current = tokens;
	return (1);
}

int			parse(t_lexer *lexer, t_env **env)
{
	char	**args;
	int		argc;
	t_token *tokens;
	int		ret;

	tokens = lexer->tokens;
	if (!tokens)
		return (g_return);
	ret = g_return;
	while (tokens)
	{
		if (!handle_operator(lexer->tokens, &tokens, &ret) || !tokens)
			return (ret);
		if (!(replace_vars(tokens, *env)))
			return (1);
		argc = build_args(&args, tokens);
		ret = execute(tokens->content, &args, env, lexer);
		end_parse(&tokens, argc, &args);
	}
	return (ret);
}
