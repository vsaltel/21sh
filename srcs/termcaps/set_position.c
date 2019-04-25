/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:59:44 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/18 18:39:24 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			move_cursor(size_t x, size_t y)
{
	char	*tmp;
	char	*tmp2;

	tmp = tgetstr("cm", NULL);
	tmp2 = tgoto(tmp, x, y);
	tputs(tmp2, 1, ft_putchar);
}

static void		move_prev_line(size_t *x, size_t *y, size_t x_dest)
{
	(*y)--;
	(*x) = x_dest;
}

void			move_pos(t_cursor_pos *pos, size_t len)
{
	if (pos->x_lastc == pos->x_max || pos->x_lastc + len > pos->x_max)
	{
		pos->y_lastc += (pos->x_lastc + 1 + len) / (pos->x_max + 1);
		pos->x_lastc = ((pos->x_lastc + 1 + len) % (pos->x_max + 1)) - 1;
		if (pos->x_lastc == (size_t)-1)
			move_prev_line(&pos->x_lastc, &pos->y_lastc, pos->x_max);
	}
	else
		pos->x_lastc += len;
	if (pos->x == pos->x_max || pos->x + len > pos->x_max)
	{
		pos->y += (pos->x + 1 + len) / (pos->x_max + 1);
		pos->x = ((pos->x + 1 + len) % (pos->x_max + 1)) - 1;
		if (pos->x == (size_t)-1)
			move_prev_line(&pos->x, &pos->y, pos->x_max);
	}
	else
		pos->x += len;
	move_cursor(pos->x, pos->y);
	pos->x_rel += len;
}

void			final_position(t_cursor_pos *pos)
{
	if (pos->y_lastc == pos->y_max - 1)
	{
		move_cursor(0, pos->y_lastc);
		tputs(tgetstr("sf", NULL), 1, ft_putchar);
		move_cursor(0, pos->y_lastc);
	}
	else
		move_cursor(0, pos->y_lastc + 1);
}

void			last_line(t_cursor_pos *pos, size_t len)
{
	size_t	line_sup;
	size_t	final_pos;
	size_t	i;

	line_sup = (pos->x_lastc + 1 + len) / (pos->x_max + 1);
	if (line_sup + pos->y_lastc >= pos->y_max)
	{
		final_pos = pos->y_max - pos->y_lastc + line_sup - 1;
		move_cursor(0, pos->y_lastc);
		i = -1;
		while (++i < final_pos)
			tputs(tgetstr("sf", NULL), 1, ft_putchar);
		pos->y_min -= final_pos;
		pos->y -= final_pos;
		move_cursor(pos->x, pos->y);
		pos->y_lastc -= final_pos;
	}
}
