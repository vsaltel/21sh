/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_left_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:58:46 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/10 17:52:05 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		maj_pos(t_cursor_pos *pos)
{
	pos->x_rel--;
	pos->x--;
	if (pos->x == -1)
	{
		pos->x = pos->x_max;
		pos->y--;
	}
}

void			termcaps_left_word(char **str, t_cursor_pos *pos
		, t_history_info *histo)
{
	(void)histo;
	if (pos->x_rel > 0 && (*str)[pos->x_rel] != ' ')
		maj_pos(pos);
	while (pos->x_rel > 0 && (*str)[pos->x_rel] == ' ')
		maj_pos(pos);
	while (pos->x_rel > 0 && (*str)[pos->x_rel - 1] != ' ')
		maj_pos(pos);
	tputs(tgoto(tgetstr("cm", NULL), pos->x, pos->y), 1, my_putchar);
}
