/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:59:44 by vsaltel           #+#    #+#             */
/*   Updated: 2019/05/02 20:33:17 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		move_pos(char *str, t_cursor_pos *pos, int len_dest)
{
	pos->len_str = ft_strlen(str);
	if (len_dest < 0)
		len_dest = 0;
	else if (len_dest > pos->len_str)
		len_dest = pos->len_str;
	pos->x_rel = len_dest;
	pos->x = pos->x_min;
	pos->y = (pos->y_min >= 0 ? pos->y_min : 0);
	if (pos->x == pos->x_max || pos->x + len_dest > pos->x_max)
	{
		pos->y += (pos->x + 1 + len_dest) / (pos->x_max + 1);
		pos->x = ((pos->x + 1 + len_dest) % (pos->x_max + 1)) - 1;
		if (pos->x == -1)
		{
			pos->y--;
			pos->x = pos->x_max;
		}
	}
	else
		pos->x += len_dest;
	move_cursor(pos->x, pos->y);
}

static void		last_line(char *str, t_cursor_pos *pos)
{
	size_t	len;
	size_t	i;

	if (pos->search_mode)
		len = (pos->x_min + ft_strlen(str) +
			ft_strlen("history_search: _") + ft_strlen(pos->s_str) +
				pos->x_max + 1) / (pos->x_max + 1);
	else
		len = (pos->x_min + ft_strlen(str) + 1) / (pos->x_max + 1);
	if (len + pos->y_min >= pos->y_max)
	{
		len = pos->y_min + len + 1 - pos->y_max;
		move_cursor(pos->x, pos->y);
		i = -1;
		while (++i < len)
			tputs(tgetstr("sf", NULL), 1, ft_putchar);
		pos->y_min -= len;
		move_cursor(0, pos->y_min);
	}
}

void			reprint(char *str, t_cursor_pos *pos, int cursor_pos)
{
	move_cursor(0, (pos->y_min >= 0 ? pos->y_min : 0));
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	last_line(str, pos);
	prompt();
	if (pos->visual_mode)
		visual_print(str, pos);
	else
		write(1, str, ft_strlen(str));
	if (pos->search_mode)
		ft_printf("\nhistory_search: %s_", pos->s_str);
	move_pos(str, pos, cursor_pos);
}

void			final_position(t_cursor_pos *pos)
{
	size_t	len;

	len = (pos->x_min + pos->len_str + 1) / (pos->x_max + 1);
	if (len + pos->y_min >= pos->y_max - 1)
	{
		move_cursor(0, pos->y_max - 1);
		tputs(tgetstr("do", NULL), 1, ft_putchar);
		move_cursor(0, pos->y_max - 1);
	}
	else
		move_cursor(0, len + pos->y_min + 1);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
}
