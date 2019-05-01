/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_up.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:58:16 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/30 15:43:42 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		termcaps_up(char **str, t_cursor_pos *pos, t_shell *shell)
{
	(void)shell;
	(void)str;
	if (!str || !*str)
		return ;
	if ((int)pos->y > 0 && ((pos->y == pos->y_min + 1 && pos->x >= pos->x_min)
		|| (pos->y > pos->y_min + 1)))
	{
		pos->y--;
		pos->x_rel -= pos->x_max + 1;
		move_cursor(pos->x, pos->y);
	}
	else if (pos->y > 0 && pos->y == pos->y_min + 1 && pos->x < pos->x_min)
	{
		pos->x = pos->x_min;
		pos->y = pos->y_min;
		pos->x_rel = 0;
		move_cursor(pos->x, pos->y);
	}
}
