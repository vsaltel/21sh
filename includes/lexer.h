/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:23:56 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/11 15:58:12 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "shell.h"

typedef enum	e_token_type
{
	TOKEN_NULL,
	TOKEN_NAME,
	TOKEN_QUOTES,
	TOKEN_DQUOTES,
	TOKEN_SEMI,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_REDIR,
	TOKEN_PIPE,
	TOKEN_IGN
}				t_token_type;

typedef struct	s_ex_token
{
	const char		*op;
	size_t			len;
	t_token_type	type;
}				t_ex_token;

typedef struct	s_token
{
	char			*content;
	size_t			len;
	t_token_type	type;
	struct s_token	*next;
}				t_token;

typedef struct	s_lexer
{
	t_token		*tokens;
	size_t		size;
}				t_lexer;

static const t_ex_token g_tokens_list[] =
{
	{"<<", 2, TOKEN_REDIR},
	{">&", 2, TOKEN_REDIR},
	{"<&", 2, TOKEN_REDIR},
	{"&&", 2, TOKEN_AND},
	{"||", 2, TOKEN_OR},
	{"|", 1, TOKEN_PIPE},
	{"<", 1, TOKEN_REDIR},
	{">", 1, TOKEN_REDIR},
	{";", 1, TOKEN_SEMI},
	{" ", 1, TOKEN_IGN},
	{"\n", 1, TOKEN_IGN},
	{"\v", 1, TOKEN_IGN},
	{"\t", 1, TOKEN_IGN},
	{"\r", 1, TOKEN_IGN},
	{"\f", 1, TOKEN_IGN},
	{NULL, 1, TOKEN_NULL}
};

int lex(char *s, t_lexer *lexer);
int is_escaped(char *s, size_t index, int endquote);
int is_start_quote(char *s, size_t index);
void destroy_lexer(t_lexer *lexer);
t_token *push_token(t_token *list, t_token *new);
t_token *create_token(t_lexer *lexer, char *content,
					  size_t len, t_token_type type);
t_ex_token search_token(const char *s);
void destroy_tokens(t_token *token);

#endif
