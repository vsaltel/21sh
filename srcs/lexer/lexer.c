/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:23:45 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/03 18:37:42 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	handle_quotes(t_lexer *lexer, char **prev, char **s)
{
	char	*str;
	char	quote;

	str = *s;
	quote = *str;
	str++;
	while (*str)
	{
		if (*str == quote && !is_escaped(*s, str - *s, 1))
			break ;
		str++;
	}
	if (!*str || *str != quote)
		return (quote == '\'' ? 0 : -1);
	(*prev)++;
	create_token(lexer, *prev, str - *prev, TOKEN_NAME);
	*prev = ++str;
	*s = str;
	return (1);
}

static int	add_quotes(t_lexer *lexer, char **s, char **prev)
{
	int		ret;

	if (*s == *prev || (*s > *prev && *((*s) - 1) != '\\'))
	{
		if ((ret = handle_quotes(lexer, prev, s)) < 1)
			return (ret);
	}
	else
		(*s)++;
	return (1);
}

static int	rlex(char *s, char *prev, t_lexer *lexer)
{
	t_ex_token	cur;
	int			ret;

	while (s && *s)
	{
		ft_printf("STATE: %d - ", lexer->state);
		if (lexer->state == ST_GENERAL)
		{
			cur = lexer_search(s);
			ft_printf("OPERATOR: |%s|", cur.op);
			if (cur.op)
			{
				//Close actual token
				s > prev ? create_token(lexer, prev, s - prev, TOKEN_NAME) : 0;
				//Add current token (except blanks)
				cur.type != TOKEN_IGN ? create_token(lexer, s, cur.len, cur.type) : 0;
				prev = (s += cur.len);
			}
			else
			{
				if (*s == '"' && !is_escaped(s, s - prev, 0))
				{
					prev = s;
					lexer->state = ST_DQUOTES;
				}
				else if (*s == '\'' && !is_escaped(s, s - prev, 0))
				{
					prev = s;
					lexer->state = ST_QUOTES;
				}
				else if (*s == '\\' && !is_escaped(s, s - prev, 0))
				{
					prev = s;
					lexer->state = ST_ESCAPED;
				}
				else if (*s == '#' && !is_escaped(s, s - prev, 0))
				{
					prev = s;
					lexer->state = ST_COMMENT;
				}
				s++;
			}
		}
		else if (lexer->state == ST_QUOTES)
		{
			ft_printf("QUOTED CHAR: %c", *s);
			if (*s == '\'' && !is_escaped(prev, s - prev, 0))
			{
				lexer->state = ST_GENERAL;
				create_token(lexer, prev, ++s - prev, TOKEN_NAME);
				prev = s;
			}
			else if (*s == '\0')
				return (0);
			else
				s++;
		}
		else if (lexer->state == ST_DQUOTES)
		{
			ft_printf("DQUOTED CHAR: %c", *s);
			if (*s == '"' && !is_escaped(prev, s - prev, 0))
			{
				lexer->state = ST_GENERAL;
				create_token(lexer, prev, ++s - prev, TOKEN_NAME);
				prev = s;
			}
			else if (*s == '\0')
				return (-1);
			else
				s++;
		}
		else if (lexer->state == ST_ESCAPED)
		{
			s++;
			ft_printf("ESCAPED CHAR: %c", *s);
			lexer->state = ST_GENERAL;
		}
		else if (lexer->state == ST_COMMENT)
		{
			ft_printf("COMMENTED CHAR: %c", *s);
			if (*s == '\n' && !is_escaped(prev, s - prev, 0))
			{
				lexer->state = ST_GENERAL;
				prev = s;
			}
			else
				s++;
		}
		ft_printf("\n");
	}
	if (lexer->state == ST_GENERAL)
		s > prev ? create_token(lexer, prev, s - prev, TOKEN_NAME) : 0;
	else
	{
		if (lexer->state == ST_DQUOTES)
			return (-1);
		if (lexer->state == ST_QUOTES)
			return (0);
	}
	return (1);
}

int			lex(char *s, t_lexer *lexer)
{
	size_t	last_char;

	if (!s)
		return (1);
	last_char = ft_strlen(s) - 1;
	if (*s && s[last_char] == '\\' && !is_escaped(s, last_char, 0))
		return (-2);
	return (rlex(s, s, lexer));
}
