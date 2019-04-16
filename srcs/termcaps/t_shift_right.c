/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shift_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:32:35 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/16 11:40:21 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		maj_pos(t_cursor_pos *pos)
{
	pos->x_rel++;
	pos->x++;
	if (pos->x > pos->x_max)
	{
		pos->x = 0;
		pos->y++;
	}
}

int		termcaps_shift_right(char **str, t_cursor_pos *pos, t_history *histo)
{
	(void)histo;
	while ((*str)[pos->x_rel] && (*str)[pos->x_rel] != ' ')
		maj_pos(pos);
	while ((*str)[pos->x_rel] && (*str)[pos->x_rel] == ' ')
		maj_pos(pos);
	tputs(tgoto(tgetstr("cm", NULL), pos->x, pos->y), 1, my_putchar);
	return (0);
}
