/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_down.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:57:00 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/10 17:52:59 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	termcaps_down(char **str, t_cursor_pos *pos, t_history_info *histo)
{
	(void)histo;
	if ((pos->y == pos->y_lastc - 1 && pos->x <= pos->x_lastc)
		|| (pos->y < pos->y_lastc - 1))
	{
		pos->y++;
		pos->x_rel += pos->x_max + 1;
		tputs(tgoto(tgetstr("cm", NULL), pos->x, pos->y), 1, my_putchar);
	}
	else if (pos->y == pos->y_lastc - 1 && pos->x > pos->x_lastc)
	{
		pos->y = pos->y_lastc;
		pos->x = pos->x_lastc;
		pos->x_rel = ft_strlen(*str);
		tputs(tgoto(tgetstr("cm", NULL), pos->x, pos->y), 1, my_putchar);
	}
}
