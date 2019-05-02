/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_position_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:24:22 by vsaltel           #+#    #+#             */
/*   Updated: 2019/05/01 18:12:07 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			reprint(char *str, t_cursor_pos *pos, size_t cursor_pos)
{
	move_cursor(0, ((int)pos->y_min >= 0 ? pos->y_min : 0));
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	last_line(str, pos);
	prompt();
	if (pos->visual_mode)
		visual_print(str, pos);
	else
		write(1, str, ft_strlen(str));
	pos->x = pos->x_min;
	pos->x_lastc = pos->x_min;
	pos->y = (int)pos->y_min >= 0 ? pos->y_min : 0;
	pos->y_lastc = (int)pos->y_min >= 0 ? pos->y_min : 0;
	pos->x_rel = 0;
	move_pos(pos, ft_strlen(str), cursor_pos);
	if (pos->search_mode)
	{
		move_cursor(0, pos->y_lastc + 1);
		ft_printf("history_search: %s_", pos->s_str);
		move_cursor(pos->x, pos->y);
	}
}

static void		get_pos_rest(char *buf, t_cursor_pos *pos, int i)
{
	int pow;

	pow = 1;
	while (buf[--i] != ';')
	{
		pos->x = pos->x + (buf[i] - '0') * pow;
		pow = pow * 10;
	}
	pow = 1;
	while (buf[--i] != '[')
	{
		pos->y = pos->y + (buf[i] - '0') * pow;
		pow = pow * 10;
	}
}

int				get_pos(t_cursor_pos *pos)
{
	int		i;
	char	c;
	char	buf[30];

	c = '\0';
	pos->x = 0;
	pos->y = 0;
	ft_memset(buf, '\0', 30);
	i = 0;
	write(1, "\033[6n", 4);
	while (c != 'R')
	{
		read(0, &c, 1);
		buf[i++] = c;
	}
	if (i-- < 2)
		return (1);
	get_pos_rest(buf, pos, i);
	move_cursor(--(pos->x), --(pos->y));
	return (0);
}

int				memset_pos(t_cursor_pos *pos)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	if (get_pos(pos))
		return (0);
	pos->x_min = pos->x;
	pos->x_lastc = pos->x;
	pos->y_lastc = pos->y;
	pos->x_rel = 0;
	pos->x_max = w.ws_col - 1;
	pos->y_min = pos->y;
	pos->y_max = w.ws_row;
	pos->compl = 0;
	pos->visual_mode = 0;
	pos->v_beg = 0;
	pos->search_mode = 0;
	pos->s_str = NULL;
	return (1);
}
