/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:59:44 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/16 18:12:53 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		move_cursor(size_t x, size_t y)
{
	char	*tmp;
	char	*tmp2;

	tmp = tgetstr("cm", NULL);
	tmp2 = tgoto(tmp, x, y);
	tputs(tmp2, 1, ft_putchar);
}

static void	move_prev_line(size_t *x, size_t *y, size_t x_dest)
{
	(*y)--;
	(*x) = x_dest;
}

void		move_pos(t_cursor_pos *pos, size_t len)
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

static int		get_pos(t_cursor_pos *pos)
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
	if (get_pos(pos))
		return (0);
	pos->x_min = pos->x;
	pos->x_lastc = pos->x;
	pos->y_lastc = pos->y;
	pos->x_rel = 0;
	pos->x_max = tgetnum("co") - 1;
	pos->y_min = pos->y;
	pos->y_max = tgetnum("li");
	return (1);
}
