/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_position_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:24:22 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/18 18:18:54 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	pos->visual_mode = 0;
	pos->compl = 0;
	pos->o_input = NULL;
	return (1);
}
