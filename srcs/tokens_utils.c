/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 12:27:16 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/03 12:21:01 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token		*push_token(t_token *list, t_token *new)
{
	while (list->next)
		list = list->next;
	if (!list)
		return (NULL);
	list->next = new;
	return (new);
}

t_token		*create_token(t_lexer *lexer, char *content,
											size_t len, t_token_type type)
{
	t_token *token;

	if (!lexer || !(token = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	if (!(token->content = ft_strndup(content, len)))
		return (NULL);
	token->len = len;
	token->type = type;
	token->next = NULL;
	if (lexer->tokens)
		push_token(lexer->tokens, token);
	else
		lexer->tokens = token;
	(lexer->size)++;
	return (token);
}

t_ex_token	search_token(const char *s)
{
	const t_ex_token	empty = {NULL, 0, TOKEN_NULL};
	size_t				i;

	if (!s)
		return (empty);
	i = 0;
	while (g_tokens_list + i && (g_tokens_list[i]).op)
	{
		if (ft_strncmp(g_tokens_list[i].op, s, g_tokens_list[i].len) == 0)
			return (g_tokens_list[i]);
		i++;
	}
	return (empty);
}
