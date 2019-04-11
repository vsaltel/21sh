/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:52:54 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/11 13:20:14 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_anode		*create_node(t_token *ope, t_cmd *cmd)
{
	t_anode	*node;

	if (!(node = (t_anode *)malloc(sizeof(t_anode))))
		exit(-1);
	node->ope = ope;
	node->cmd = cmd;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return (node);
}
