/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_visual_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:30:28 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/18 18:35:49 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	reprint(char *str, t_cursor_pos *pos)
{
	size_t	line_sup;
	size_t	len;

	if (pos->y_lastc > pos->y_min)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, pos->y_min + 1), 1, ft_putchar);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
	}
	tputs(tgoto(tgetstr("cm", NULL), pos->x_min, pos->y_min), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
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
	pos->x_rel = 0;
	move_pos(pos, ft_strlen(str));
}

void		termcaps_visual_mode(char **str, t_cursor_pos *pos, t_shell *shell)
{
	(void)str;
	(void)shell;
	if (!pos->visual_mode)
	{
		pos->visual_mode = 1;
		pos->visual_str = ft_strndup(*str + pos->x_rel, 1);
		if ((*str)[pos->x_rel])
		{
			tputs(tgetstr("dc", NULL), 1, ft_putchar);
			ft_printf("\e[7m%c\e[0m", (*str)[pos->x_rel]);
		}
	}
	else
	{
		pos->visual_mode = 0;
		ft_strdel(&(pos->visual_str));
		reprint(*str, pos);
	}
}
