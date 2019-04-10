/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:11:08 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/10 12:50:40 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int			is_redirection(t_token *token)
{
	return (token->type == TOKEN_REDIRI || token->type == TOKEN_REDIRO);
}

static t_redirect	*create_redirection(t_token *token)
{
	t_redirect	*red;
	size_t		skip;

	if (!token || !(red = (t_redirect *)malloc(sizeof(t_redirect))))
		return (NULL);
	red->done = 0;
	skip = 0;
	if (token->type == TOKEN_REDIRO)
		red->filedes = ft_atoi_i(token->content, &skip);
	red->type = token->type;
	red->append = ft_strcmp(token->type == TOKEN_REDIRO ? ">>" : "<<",
												token->content + skip) == 0;
	red->value = token->next;
	return (red);
}

t_redirect			*parse_redirections(t_token *tok, int offset)
{
	t_redirect	*red;

	while (tok && offset--)
		tok = tok->next;
	if (!tok || !tok->next || !is_redirection(tok))
		return (NULL);
	red = NULL;
	ft_printf("Redir: %s\n", tok->content);
	while (tok)
	{
		if (!red)
			red = create_redirection(tok);
		else
			red->next = create_redirection(tok);
		tok = tok->next->next;
	}
	return (red);
}
