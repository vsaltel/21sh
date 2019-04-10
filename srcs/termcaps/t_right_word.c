/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_right_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:58:58 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/10 17:51:48 by vsaltel          ###   ########.fr       */
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

void			termcaps_right_word(char **str, t_cursor_pos *pos
		, t_history_info *histo)
{
	(void)histo;
	while ((*str)[pos->x_rel] && (*str)[pos->x_rel] != ' ')
		maj_pos(pos);
	while ((*str)[pos->x_rel] && (*str)[pos->x_rel] == ' ')
		maj_pos(pos);
	tputs(tgoto(tgetstr("cm", NULL), pos->x, pos->y), 1, my_putchar);
}
