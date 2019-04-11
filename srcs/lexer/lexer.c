/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:23:45 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/11 17:59:26 by frossiny         ###   ########.fr       */
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

static int	rlex(char *s, char *prev, t_lexer *lexer)
{
	t_ex_token	cur;
	int			tmp;

	while (s && *s)
	{
		//ft_printf("STATE: %d - ", lexer->state);
		if (lexer->state == ST_GENERAL)
		{
			cur = lexer_search(s);
			//ft_printf("OPERATOR: |%s|", cur.op);
			if (cur.op)
			{
				//Close actual token
				s > prev ? create_token(lexer, prev, s - prev, TOKEN_NAME) : 0;
				//Add current token (except blanks)
				cur.type != TOKEN_IGN ? create_token(lexer, s, cur.len, cur.type) : 0;
				lexer->state = cur.state;
				prev = (s += cur.len);
			}
			else if (ft_isdigit(*s) && (tmp = is_redirection_o(s)))
			{
				//Close actual token
				s > prev ? create_token(lexer, prev, s - prev, TOKEN_NAME) : 0;
				create_token(lexer, s, tmp, TOKEN_REDIRO);
				lexer->state = ST_OPERATOR;
				prev = (s += tmp);
			}
			else
			{
				//ft_printf("PREV: |%s| - S: |%s| - INDEX: %d\n", prev, s, s - prev);
				if (*s == '"' && !is_escaped(s, s - prev, 0))
				{
					prev = s;
					lexer->state = ST_DQUOTES;
				}
				else if (*s == '\'' && !is_escaped(prev, s - prev, 0))
				{
					prev = s;
					lexer->state = ST_QUOTES;
				}
				else if (*s == '\\' && !is_escaped(prev, s - prev, 0))
				{
					prev = s;
					lexer->state = ST_ESCAPED;
				}
				else if (*s == '#' && !is_escaped(prev, s - prev, 0))
				{
					prev = s;
					lexer->state = ST_COMMENT;
				}
				s++;
			}
		}
		else if (lexer->state == ST_QUOTES)
		{
			//ft_printf("QUOTED CHAR: %c", *s);
			if (*s == '\'' && !is_escaped(prev, s - prev, 0))
			{
				lexer->state = ST_GENERAL;
				create_token(lexer, prev + 1, s - prev - 1, TOKEN_QUOTES);
				prev = ++s;
			}
			else if (*s == '\0')
				return (0);
			else
				s++;
		}
		else if (lexer->state == ST_DQUOTES)
		{
			//ft_printf("DQUOTED CHAR: %c", *s);
			if (*s == '"' && !is_escaped(prev, s - prev, 0))
			{
				lexer->state = ST_GENERAL;
				create_token(lexer, prev + 1, s - prev - 1, TOKEN_DQUOTES);
				prev = ++s;
			}
			else if (*s == '\0')
				return (-1);
			else
				s++;
		}
		else if (lexer->state == ST_ESCAPED)
		{
			s++;
			//ft_printf("ESCAPED CHAR: %c", *s);
			lexer->state = ST_GENERAL;
		}
		else if (lexer->state == ST_COMMENT)
		{
			//ft_printf("COMMENTED CHAR: %c", *s);
			if (*s == '\n' && !is_escaped(prev, s - prev, 0))
			{
				lexer->state = ST_GENERAL;
				prev = s;
			}
			else
				s++;
		}
		else if (lexer->state == ST_OPERATOR)
		{
			cur = lexer_search(s);
			if (cur.op && cur.type != TOKEN_IGN)
			{
				write(2, "21sh: parse error near '", 24);
				write(2, cur.op, cur.len);
				ft_putstr_fd("'\n", 2);
				return (0);
			}
			else if (cur.op)
			{
				s += cur.len;
				prev += cur.len;
			}
			else
				lexer->state = ST_GENERAL;
		}
		else if (lexer->state == ST_SEMIC)
		{
			cur = lexer_search(s);
			if (cur.op && cur.type != TOKEN_IGN)
			{
				write(2, "21sh: parse error near '", 24);
				write(2, cur.op, cur.len);
				ft_putstr_fd("'\n", 2);
				return (0);
			}
			else
				lexer->state = ST_GENERAL;
		}
		//ft_printf("\n");
	}
	if (lexer->state == ST_GENERAL)
		s > prev ? create_token(lexer, prev, s - prev, TOKEN_NAME) : 0;
	else
	{
		if (lexer->state == ST_DQUOTES)
			return (-3);
		else if (lexer->state == ST_QUOTES)
			return (-2);
		else if (lexer->state == ST_SEMIC)
			return (1);
		else
		{
			write(2, "21sh: parse error near '", 24);
			write(2, prev, s - prev + 1);
			ft_putstr_fd("'\n", 2);
			return (-1);
		}
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
		return (-4);
	return (rlex(s, s, lexer));
}
