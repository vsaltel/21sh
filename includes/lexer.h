/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:23:56 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/08 15:06:19 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "shell.h"

typedef enum	e_state
{
	ST_GENERAL,
	ST_QUOTES,
	ST_DQUOTES,
	ST_ESCAPED,
	ST_COMMENT,
	ST_OPERATOR,
	ST_SEMIC
}				t_state;

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
	t_state			state;
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
	t_state		state;
}				t_lexer;

static const t_ex_token g_tokens_list[] =
{
	{"<<", 2, TOKEN_REDIR, ST_OPERATOR},
	{">>", 2, TOKEN_REDIR, ST_OPERATOR},
	{">&", 2, TOKEN_REDIR, ST_OPERATOR},
	{"<&", 2, TOKEN_REDIR, ST_OPERATOR},
	{"&&", 2, TOKEN_AND, ST_OPERATOR},
	{"||", 2, TOKEN_OR, ST_OPERATOR},
	{"|", 1, TOKEN_PIPE, ST_OPERATOR},
	{"<", 1, TOKEN_REDIR, ST_OPERATOR},
	{">", 1, TOKEN_REDIR, ST_OPERATOR},
	{";", 1, TOKEN_SEMI, ST_SEMIC},
	{" ", 1, TOKEN_IGN, ST_GENERAL},
	{"\n", 1, TOKEN_IGN, ST_GENERAL},
	{"\v", 1, TOKEN_IGN, ST_GENERAL},
	{"\t", 1, TOKEN_IGN, ST_GENERAL},
	{"\r", 1, TOKEN_IGN, ST_GENERAL},
	{"\f", 1, TOKEN_IGN, ST_GENERAL},
	{NULL, 1, TOKEN_NULL, ST_GENERAL}
};

int 		lex(char *s, t_lexer *lexer);
int 		is_escaped(char *s, size_t index, int endquote);
t_ex_token	lexer_search(const char *s);
void 		destroy_lexer(t_lexer *lexer);
t_token 	*push_token(t_token *list, t_token *new);
t_token 	*create_token(t_lexer *lexer, char *content,
						size_t len, t_token_type type);
void		destroy_tokens(t_token *token);
int			is_word_token(t_token *token);


#endif
