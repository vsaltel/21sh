/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_right.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:34:17 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/29 14:49:35 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		termcaps_right(char **str, t_cursor_pos *pos, t_shell *shell)
{
	(void)shell;
	(void)str;
	if (!str || !*str)
		return ;
	if ((pos->x < pos->x_lastc
		|| (pos->y < pos->y_lastc && pos->x < pos->x_max))
		|| (pos->y < pos->y_lastc && pos->x < pos->x_max))
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
		++(pos->x);
		++(pos->x_rel);
	}
	else if (pos->y < pos->y_lastc && pos->x == pos->x_max)
	{
		move_cursor((pos->x = 0), ++(pos->y));
		++(pos->x_rel);
	}
}
