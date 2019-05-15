/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:11:08 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/15 14:54:34 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static int			is_redirection(t_token *token)
{
	return (token->type == TOKEN_REDIRI
			|| token->type == TOKEN_REDIRO
			|| token->type == TOKEN_AGGR);
}

static int			is_append(t_token *token)
{
	if (token->type == TOKEN_REDIRI)
		return (ft_strstr(token->content, "<<") != NULL);
	else if (token->type == TOKEN_REDIRO)
		return (ft_strstr(token->content, ">>") != NULL);
	else
		return (0);
}

static t_redirect	*create_redirection(t_token *token)
{
	t_redirect	*red;
	size_t		skip;

	if (!token || !(red = (t_redirect *)malloc(sizeof(t_redirect))))
		return (NULL);
	red->done = 0;
	skip = 0;
	red->p[0] = -1;
	red->p[1] = -1;
	if (ft_isdigit(token->content[0]))
		red->filedes = ft_atoi_i(token->content, &skip);
	else
	{
		if (token->type != TOKEN_AGGR)
			red->filedes = (token->type == TOKEN_REDIRO) ? 1 : 0;
		else
			red->filedes = (ft_strstr(token->content, "&>")) ? 1 : 0;
	}
	red->type = token->type;
	red->append = is_append(token);
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
