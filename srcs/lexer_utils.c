/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 12:02:17 by frossiny          #+#    #+#             */
/*   Updated: 2019/03/07 14:00:07 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_escaped(char *s, size_t index, int endquote)
{
	int	prev;

	prev = 0;
	if (index == 0)
		return (0);
	if (s[index - 1] == '\\')
		prev = !is_escaped(s, index - 1, 0);
	if (s[index] == '\'' && endquote)
		return (0);
	return (prev);
}

int		is_start_quote(char *s, size_t index)
{
	if (s[index] != '\'' && s[index] != '"')
		return (0);
	return (is_escaped(s, index, 0));
}

void	destroy_tokens(t_token *token)
{
	t_token		*next;

	next = NULL;
	while (token)
	{
		next = token->next;
		free(token->content);
		free(token);
		token = next;
	}
}

void	destroy_lexer(t_lexer *lexer)
{
	destroy_tokens(lexer->tokens);
	lexer->tokens = NULL;
	lexer->size = 0;
}
