/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:59:44 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/26 18:20:21 by vsaltel          ###   ########.fr       */
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

void			move_pos(t_cursor_pos *pos, size_t len, size_t len_dest)
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
	if (pos->x == pos->x_max || pos->x + len_dest > pos->x_max)
	{
		pos->y += (pos->x + 1 + len_dest) / (pos->x_max + 1);
		pos->x = ((pos->x + 1 + len_dest) % (pos->x_max + 1)) - 1;
		if (pos->x == (size_t)-1)
			move_prev_line(&pos->x, &pos->y, pos->x_max);
	}
	else
		pos->x += len_dest;
	move_cursor(pos->x, pos->y);
	pos->x_rel += len_dest;
}

void			final_position(t_cursor_pos *pos)
{
	if (pos->y_lastc == pos->y_max - 1)
	{
		move_cursor(0, pos->y_lastc);
		tputs(tgetstr("do", NULL), 1, ft_putchar);
		move_cursor(0, pos->y_lastc);
	}
	else
		move_cursor(0, pos->y_lastc + 1);
}

void			last_line(char *str, t_cursor_pos *pos)
{
	size_t	len;
	size_t	i;

	len = (pos->x_min + ft_strlen(str) + 1) / (pos->x_max + 1);
	if (len + pos->y_min >= pos->y_max)
	{
		len = pos->y_min + len + 1 - pos->y_max;
		i = -1;
		while (++i < len)
			tputs(tgetstr("do", NULL), 1, ft_putchar);
		pos->y_min -= len;
		move_cursor(0, pos->y_min);
	}
}
