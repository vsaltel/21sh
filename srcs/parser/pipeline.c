/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:28:42 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/11 13:08:22 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_pipel	*create_pipel(t_pipel *prev, t_cmd *cmd)
{
	t_pipel		*new;

	if (!(new = (t_pipel *)malloc(sizeof(t_pipel))))
		return (NULL);
	new->cmd = cmd;
	new->previous = prev;
	new->next = NULL;
	return (new);
}

t_pipel			*build_pipeline(t_anode *node)
{
	t_pipel	*pipel;
	t_pipel *curr;

	ft_printf("Pipeline start: %s\n", node->ope ? node->ope->content : node->cmd->exe->content);
	pipel = create_pipel(NULL, node->cmd);
	curr = pipel;
	node = node->parent;
	while (node && node->ope)
	{
		ft_printf("Pipeline: %s\n", node->ope ? node->ope->content : node->cmd->exe->content);
		curr->next = create_pipel(curr, node->right->cmd);
		curr = curr->next;
		node = node->parent;
	}
	return (pipel);
}

void			del_pipeline(t_pipel *pline)
{
	t_pipel		*next;

	while (pline)
	{
		next = pline->next;
		free(pline);
		pline = next;
	}
}
