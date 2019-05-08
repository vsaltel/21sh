/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_visual_cut.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:55:07 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/29 14:56:00 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		termcaps_visual_cut(char **str, t_cursor_pos *pos, t_shell *shell)
{
	(void)shell;
	if (!str || !*str || !pos->visual_mode)
		return ;
	pos->visual_mode = 0;
	ft_strdel(&pos->v_str);
	if (pos->v_beg < pos->x_rel)
	{
		pos->v_str = ft_strndup(*str + pos->v_beg, pos->x_rel - pos->v_beg + 1);
		*str = ft_strfcut(*str, pos->v_beg, pos->x_rel);
		pos->x_rel = pos->v_beg;
	}
	else
	{
		pos->v_str = ft_strndup(*str + pos->x_rel, pos->v_beg - pos->x_rel + 1);
		*str = ft_strfcut(*str, pos->x_rel, pos->v_beg);
	}
}
