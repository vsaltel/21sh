/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shift_left.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:25:50 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/16 18:14:13 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		maj_pos(t_cursor_pos *pos)
{
	pos->x_rel--;
	pos->x--;
	if ((int)pos->x == -1)
	{
		pos->x = pos->x_max;
		pos->y--;
	}
	ft_printf("pos new : x %d y %d\n", pos->x, pos->y);
}

int		termcaps_shift_left(char **str, t_cursor_pos *pos, t_history *histo)
{
	ft_printf("pos ini : x %d y %d\n", pos->x, pos->y);
	if (pos->x_rel > 0 && (*str)[pos->x_rel] != ' ')
		maj_pos(pos);
	while (pos->x_rel > 0 && (*str)[pos->x_rel] == ' ')
		maj_pos(pos);
	while (pos->x_rel > 0 && (*str)[pos->x_rel - 1] != ' ')
		maj_pos(pos);
	move_cursor(pos->x, pos->y);
	return (0);
}
