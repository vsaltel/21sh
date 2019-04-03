/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_up.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:54:25 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/03 12:21:01 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		termcaps_up(char **str, t_cursor_pos *pos)
{
	if ((pos->y == pos->y_min + 1 && pos->x >= pos->x_min) || (pos->y > pos->y_min + 1))
	{
		pos->y--;
		pos->x_rel -= pos->x_max + 1;
		tputs(tgoto(tgetstr("cm", NULL), pos->x, pos->y), 1, my_putchar);
	}
	else if (pos->y == pos->y_min + 1 && pos->x < pos->x_min)
	{
		pos->x = pos->x_min;
		pos->y = pos->y_min;
		pos->x_rel = 0;
		tputs(tgoto(tgetstr("cm", NULL), pos->x, pos->y), 1, my_putchar);
	}
	return (0);
}
