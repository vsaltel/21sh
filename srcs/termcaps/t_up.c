/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_up.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:58:16 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/15 16:00:28 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		termcaps_up(char **str, t_cursor_pos *pos, t_history *histo)
{
	(void)histo;
	(void)str;
	if ((pos->y == pos->y_min + 1 && pos->x >= pos->x_min)
		|| (pos->y > pos->y_min + 1))
	{
		pos->y--;
		pos->x_rel -= pos->x_max + 1;
		tputs(tgoto(tgetstr("cm", NULL), pos->x, pos->y), 1, ft_putchar);
	}
	else if (pos->y == pos->y_min + 1 && pos->x < pos->x_min)
	{
		pos->x = pos->x_min;
		pos->y = pos->y_min;
		pos->x_rel = 0;
		tputs(tgoto(tgetstr("cm", NULL), pos->x, pos->y), 1, ft_putchar);
	}
}
