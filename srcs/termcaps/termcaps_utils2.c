/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:54:29 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/10 20:12:40 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			my_putchar(int c)
{
	char x;

	x = (char)c;
	write(1, &x, 1);
	return (c);
}

int			read_all(int fd, char **dest)
{
	char	buf[BUFF_SIZE];
	char	*str;
	int		ret;

	str = NULL;
	while ((ret = read(fd, buf, BUFF_SIZE - 1)))
	{
		if (ret == -1)
			break ;
		buf[ret] = '\0';
		if (!str)
			str = ft_strdup(buf);
		else
			str = ft_strfjoin(str, buf, str);
		if (ret < BUFF_SIZE - 1)
			break ;
	}
	*dest = str;
	return (ret);
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
		if (pos->x_lastc == -1)
			move_prev_line(&pos->x_lastc, &pos->y_lastc, pos->x_max);
	}
	else
		pos->x_lastc += len;
	if (pos->x == pos->x_max || pos->x + len > pos->x_max)
	{
		pos->y += (pos->x + 1 + len) / (pos->x_max + 1);
		pos->x = ((pos->x + 1 + len) % (pos->x_max + 1)) - 1;
		if (pos->x == -1)
			move_prev_line(&pos->x, &pos->y, pos->x_max);
	}
	else
		pos->x += len;
	tputs(tgoto(tgetstr("cm", NULL), pos->x, pos->y), 1, my_putchar);
	pos->x_rel += len;
}

int			memset_all(char **str, t_history **history, t_history_info *histo
		, t_cursor_pos *pos)
{
	g_clear_buffer = 0;
	*str = NULL;
	*histo = memset_history(history);
	if (!memset_pos(pos))
		return (0);
	return (1);
}
