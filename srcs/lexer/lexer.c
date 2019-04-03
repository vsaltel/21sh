/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:23:45 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/03 14:13:31 by frossiny         ###   ########.fr       */
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
	create_token(lexer, *prev, str - *prev,
				quote == '"' ? TOKEN_DQUOTES : TOKEN_QUOTES);
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

static void	add_current_token(t_lexer *lexer, t_ex_token cur,
												char **s, char **prev)
{
	*s += cur.len;
	if (cur.type != TOKEN_IGN)
		create_token(lexer, (char *)cur.op, cur.len, cur.type);
	*prev = *s;
}

static int	rlex(char *s, char *prev, t_lexer *lexer)
{
	t_ex_token	cur;
	int			ret;

	while (s && *s)
	{
		if (*s == '\\' && s++)
			continue;
		cur = search_token(s);
		if (((cur.op && !is_escaped(prev, s - prev, 0))
						|| is_start_quote(s, prev - s)) && prev != s)
			create_token(lexer, prev, s - prev, TOKEN_NAME);
		if (cur.op && !is_escaped(prev, s - prev, 0))
			add_current_token(lexer, cur, &s, &prev);
		else if (*s == '"' || *s == '\'')
		{
			if ((ret = add_quotes(lexer, &s, &prev)) < 1)
				return (ret);
		}
		else
			s++;
	}
	(prev != s) ? create_token(lexer, prev, s - prev, TOKEN_NAME) : 0;
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
