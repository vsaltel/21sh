/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:52:54 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/10 13:03:36 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
static void	copy_ope(t_anode *node, t_token *ope)
{
	node->ope.type = ope->type;
	node->ope.content = ft_strdup(ope->content);
	node->ope.len = ope->len;
	node->ope.next = NULL;
}
*/

t_anode		*create_node(t_token *ope, t_cmd *cmd)
{
	t_anode	*node;

	if (!(node = (t_anode *)malloc(sizeof(t_anode))))
		exit (-1);
	node->ope = ope;
	node->cmd = cmd;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return (node);
}
