/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:58:30 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/29 16:09:51 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_childs	*child_add(t_childs **childs, int pid)
{
	t_childs	*curr;
	t_childs	*new;

	if (!childs || !(new = (t_childs *)malloc(sizeof(t_childs))))
		return (NULL);
	new->pid = pid;
	new->next = NULL;
	if (*childs)
	{
		curr = *childs;
		while (curr && curr->next)
			curr = curr->next;
		curr->next = new;
	}
	else
		*childs = new;
	return (new);
}

void		child_del(t_childs *childs)
{
	t_childs *list;

	while (childs)
	{
		list = childs->next;
		free(childs);
		childs = list;
	}
}
