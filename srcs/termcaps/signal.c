/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 13:17:57 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/18 18:38:24 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	reprint(char *str, t_cursor_pos *pos)
{
	size_t	line_sup;

	if (pos->y_lastc > pos->y_min)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, pos->y_min + 1), 1, ft_putchar);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
	}
	tputs(tgoto(tgetstr("cm", NULL), 0, pos->y_min), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	g_return ? ft_printf("\033[1;31m$> \033[0m")
		: ft_printf("\033[1;32m$> \033[0m");
	write(1, str, ft_strlen(str));
	line_sup = (pos->x_lastc + 1 + ft_strlen(str)) / (pos->x_max + 1);
	if (line_sup + pos->y_lastc >= pos->y_max)
	{
		pos->y_min -= pos->y_max - pos->y_lastc + line_sup - 1;
		pos->y_lastc -= pos->y_max - pos->y_lastc + line_sup - 1;
	}
	pos->x = pos->x_min;
	pos->x_lastc = pos->x_min;
	pos->y = pos->y_min;
	pos->y_lastc = pos->y_min;
	line_sup = pos->x_rel;
	pos->x_rel = 0;
	move_pos(pos, line_sup);
}

void		resize(int sig)
{
	struct winsize	w;
	t_cursor_pos	tmp;

	(void)sig;
	ioctl(0, TIOCGWINSZ, &w);
	if (!get_pos(&tmp))
	{
		if (tmp.y != g_pos.y)
		{
			if (tmp.x < g_pos.x)
				g_pos.y_min--;
			if (tmp.x > g_pos.x)
				g_pos.y_min++;
		}
	}
	g_pos.x_max = w.ws_col - 1;
	g_pos.y_max = w.ws_row;
	reprint(g_pos.str, &g_pos);
}
