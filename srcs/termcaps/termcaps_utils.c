/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 19:16:48 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/10 19:05:49 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				termcaps_init(void)
{
	int				ret;
	char			*term_var;
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_lflag &= ~(OPOST);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
	if (!(term_var = getenv("TERM")))
	{
		ft_printf("var TERM non trouve");
		return (-1);
	}
	if ((ret = tgetent(NULL, term_var)) != 1)
		return (-1);
	return (ret);
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
	tputs(tgoto(tgetstr("cm", NULL), --(pos->x), --(pos->y)), 1, my_putchar);
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

void			final_position(t_cursor_pos *pos)
{
	if (pos->y_lastc == pos->y_max - 1)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, pos->y_lastc), 1, my_putchar);
		tputs(tgetstr("sf", NULL), 1, my_putchar);
		tputs(tgoto(tgetstr("cm", NULL), 0, pos->y_lastc), 1, my_putchar);
	}
	else
		tputs(tgoto(tgetstr("cm", NULL), 0, pos->y_lastc + 1), 1, my_putchar);
}
