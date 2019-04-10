/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:14:27 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/08 16:37:21 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		build_args(char ***args, t_token *tokens)
{
	int		argc;
	int		i;
	t_token	*tmp;

	argc = 0;
	tmp = tokens;
	while (tmp && is_word_token(tmp))
	{
		if (ft_strisdigit(tmp->content) && tmp->next
		&& tmp->next->type == TOKEN_REDIRI && tmp->next->type == TOKEN_REDIRO)
			break ;
		argc++;
		tmp = tmp->next;
	}
	if (!((*args) = (char **)malloc(sizeof(char *) * (argc + 1))))
		exit(-1);
	tmp = tokens;
	i = 0;
	while (tmp && i < argc)
	{
		(*args)[i++] = tmp->content;
		tmp = tmp->next;
	}
	(*args)[i] = NULL;
	return (argc);
}
