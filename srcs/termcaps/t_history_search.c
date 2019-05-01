/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_history_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 12:28:48 by vsaltel           #+#    #+#             */
/*   Updated: 2019/05/01 14:31:51 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		history_search_replace(char **str, char *buf, t_cursor_pos *pos
		, t_history *histo)
{
	t_histo_lst	*curr;
	char		*tmp;

	if (!pos->s_str)
		pos->s_str = ft_strdup(buf);
	else
		pos->s_str = ft_strfjoin(pos->s_str, buf, pos->s_str);
	curr = histo->lst;
	while (curr)
	{
		ft_strdel(str);
		if ((tmp = ft_strstr(curr->str, pos->s_str)))
		{
			*str = ft_strdup(curr->str);
			pos->x_rel = tmp - curr->str - 1;
			break ;
		}
		curr = curr->next;
	}
}

void		termcaps_history_search(char **str, t_cursor_pos *pos
		, t_shell *shell)
{
	if (pos->visual_mode)
		return ;
	if (pos->search_mode)
	{
		ft_strdel(str);
		pos->x_rel = 0;
		ft_strdel(&pos->s_str);
		pos->search_mode = 0;
	}
	else
	{
		ft_strdel(&pos->s_str);
		pos->search_mode = 1;
	}
}
