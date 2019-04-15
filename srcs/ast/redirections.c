/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:11:08 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/15 12:03:35 by frossiny         ###   ########.fr       */
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
	red->filedes = 0;
	if (token->type == TOKEN_REDIRO)
	{
		if ((red->filedes = ft_atoi_i(token->content, &skip)) == 0)
			red->filedes = 1;
	}
	red->type = token->type;
	red->append = ft_strcmp(token->type == TOKEN_REDIRO ? ">>" : "<<",
												token->content + skip) == 0;
	red->value = token->next;
	red->next = NULL;
	return (red);
}

t_redirect			*parse_redirections(t_token *tok, int offset)
{
	t_redirect	*red;

	if (offset < 0)
		return (NULL);
	while (tok && offset--)
		tok = tok->next;
	if (!tok || !tok->next || !is_redirection(tok))
		return (NULL);
	red = NULL;
	while (tok && is_redirection(tok))
	{
		if (!red)
			red = create_redirection(tok);
		else
			red->next = create_redirection(tok);
		tok = tok->next->next;
	}
	return (red);
}
