/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:17:47 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/12 14:58:43 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	is_redirection_o(char *str)
{
	int			i;
	t_ex_token	cur;

	i = 0;
	if (!ft_isdigit(*str))
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	cur = lexer_search(str + i);
	if (cur.op && cur.type == TOKEN_REDIRO)
		return (i + cur.len);
	return (0);
}

static void	lex_state_general_else(t_lexer *lexer)
{
	if (*(lexer->in) == '"'
						&& !is_escaped(lexer->in, lexer->in - lexer->pin, 0))
	{
		lexer->pin = lexer->in;
		lexer->state = ST_DQUOTES;
	}
	else if (*(lexer->in) == '\''
						&& !is_escaped(lexer->pin, lexer->in - lexer->pin, 0))
	{
		lexer->pin = lexer->in;
		lexer->state = ST_QUOTES;
	}
	else if (*(lexer->in) == '\\'
						&& !is_escaped(lexer->pin, lexer->in - lexer->pin, 0))
	{
		lexer->pin = lexer->in;
		lexer->state = ST_ESCAPED;
	}
	else if (*(lexer->in) == '#'
						&& !is_escaped(lexer->pin, lexer->in - lexer->pin, 0))
	{
		lexer->pin = lexer->in;
		lexer->state = ST_COMMENT;
	}
	lexer->in++;
}

int			lex_state_general(t_lexer *lexer)
{
	t_ex_token	cur;
	int			tmp;

	cur = lexer_search(lexer->in);
	if (cur.op)
	{
		if (lexer->in > lexer->pin)
			create_token(lexer, lexer->pin, lexer->in - lexer->pin, TOKEN_NAME);
		if (cur.type != TOKEN_IGN)
			create_token(lexer, lexer->in, cur.len, cur.type);
		lexer->state = cur.state;
		lexer->pin = (lexer->in += cur.len);
	}
	else if (ft_isdigit(*(lexer->in)) && (tmp = is_redirection_o(lexer->in)))
	{
		if (lexer->in > lexer->pin)
			create_token(lexer, lexer->pin, lexer->in - lexer->pin, TOKEN_NAME);
		create_token(lexer, lexer->in, tmp, TOKEN_REDIRO);
		lexer->state = ST_OPERATOR;
		lexer->pin = (lexer->in += tmp);
	}
	else
		lex_state_general_else(lexer);
	return (1);
}
