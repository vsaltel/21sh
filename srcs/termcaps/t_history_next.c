/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_history_next.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:58:32 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/10 17:53:31 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	new_pos(t_history *curr, t_cursor_pos *pos)
{
	size_t	line_sup;

	if (pos->y_lastc > pos->y_min)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, pos->y_min + 1), 1, my_putchar);
		tputs(tgetstr("cd", NULL), 1, my_putchar);
	}
	tputs(tgoto(tgetstr("cm", NULL), pos->x_min, pos->y_min), 1, my_putchar);
	tputs(tgetstr("ce", NULL), 1, my_putchar);
	ft_printf("%s", curr->str);
	pos->x = pos->x_min;
	pos->x_lastc = pos->x_min;
	pos->y = pos->y_min;
	pos->y_lastc = pos->y_min;
	pos->x_rel = 0;
	line_sup = (pos->x_lastc + 1 + curr->len) / (pos->x_max + 1);
	if (line_sup + pos->y_lastc >= pos->y_max)
		pos->y_min -= pos->y_max - pos->y_lastc + line_sup - 1;
	move_pos(pos, curr->len);
}

void		termcaps_history_next(char **str, t_cursor_pos *pos
		, t_history_info *histo)
{
	size_t		i;
	t_history	*curr;

	if (!histo->history || !*histo->history
		|| histo->history_line == histo->history_size)
		return ;
	if (histo->history_line < histo->history_size)
		histo->history_line++;
	curr = *histo->history;
	i = 0;
	while (++i < histo->history_line && curr->next)
		curr = curr->next;
	new_pos(curr, pos);
	if (histo->history_line == 1 && *str)
		histo->first_command = ft_strdup(*str);
	if (str)
		free(*str);
	*str = ft_strdup(curr->str);
}
