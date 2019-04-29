/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_visual_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:48:01 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/29 14:55:56 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		termcaps_visual_copy(char **str, t_cursor_pos *pos, t_shell *shell)
{
	(void)shell;
	if (!str || !*str || !pos->visual_mode)
		return ;
	pos->visual_mode = 0;
	ft_strdel(&pos->v_str);
	if (pos->v_beg < pos->x_rel)
	{
		pos->v_str = ft_strndup(*str + pos->v_beg, pos->x_rel - pos->v_beg + 1);
		pos->x_rel = pos->v_beg;
	}
	else
		pos->v_str = ft_strndup(*str + pos->x_rel, pos->v_beg - pos->x_rel + 1);
}
