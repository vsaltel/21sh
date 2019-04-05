/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shift_left.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:25:50 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/05 17:47:01 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		maj_pos(t_cursor_pos *pos)
{
	pos->x_rel--;
	pos->x--;
	if (pos->x == -1)
	{
		pos->x = pos->x_max;
		pos->y--;
	}
}

int		termcaps_shift_left(char **str, t_cursor_pos *pos)
{
	if (pos->x_rel > 0 && (*str)[pos->x_rel] != ' ')
		maj_pos(pos);
	while (pos->x_rel > 0 && (*str)[pos->x_rel] == ' ')
		maj_pos(pos);
	while (pos->x_rel > 0 && (*str)[pos->x_rel - 1] != ' ')
		maj_pos(pos);
	tputs(tgoto(tgetstr("cm", NULL), pos->x, pos->y), 1, my_putchar);
	return (0);
}
