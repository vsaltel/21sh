/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_left.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:33:37 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/11 14:49:06 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		termcaps_left(char **str, t_cursor_pos *pos, t_history_info *histo)
{
	(void)histo;
	(void)str;
	if (pos->x > pos->x_min || (pos->y > pos->y_min && pos->x > 0))
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		pos->x--;
		pos->x_rel--;
	}
	else if (pos->y > pos->y_min && pos->x == 0)
	{
		pos->x = pos->x_max;
		pos->y--;
		pos->x_rel--;
		tputs(tgoto(tgetstr("cm", NULL), pos->x, pos->y), 1, ft_putchar);
	}
}
