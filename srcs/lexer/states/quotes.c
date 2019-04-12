/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:20:34 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/12 14:52:55 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		lex_state_quotes(t_lexer *lexer)
{
	if (*(lexer->in) == '\''
					&& !is_escaped(lexer->pin, lexer->in - lexer->pin, 0))
	{
		lexer->state = ST_GENERAL;
		create_token(lexer, lexer->pin + 1,
									lexer->in - lexer->pin - 1, TOKEN_QUOTES);
		lexer->pin = ++(lexer->in);
	}
	else if (*(lexer->in) == '\0')
		return (-2);
	else
		lexer->in++;
	return (1);
}

int		lex_state_dquotes(t_lexer *lexer)
{
	if (*(lexer->in) == '"'
						&& !is_escaped(lexer->pin, lexer->in - lexer->pin, 0))
	{
		lexer->state = ST_GENERAL;
		create_token(lexer, lexer->pin + 1,
									lexer->in - lexer->pin - 1, TOKEN_DQUOTES);
		lexer->pin = ++(lexer->in);
	}
	else if (*(lexer->in) == '\0')
		return (-3);
	else
		lexer->in++;
	return (1);
}
