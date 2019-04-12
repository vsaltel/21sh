/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_history_prev.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:57:50 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/11 14:49:34 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	new_pos(char **str, t_history *curr, t_cursor_pos *pos)
{
	size_t	line_sup;

	if (pos->y_lastc > pos->y_min)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, pos->y_min + 1), 1, ft_putchar);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
	}
	tputs(tgoto(tgetstr("cm", NULL), pos->x_min, pos->y_min), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	ft_printf("%s", *str);
	pos->x = pos->x_min;
	pos->x_lastc = pos->x_min;
	pos->y = pos->y_min;
	pos->y_lastc = pos->y_min;
	pos->x_rel = 0;
	line_sup = (pos->x_lastc + 1 + ft_strlen(*str)) / (pos->x_max + 1);
	if (line_sup + pos->y_lastc >= pos->y_max)
		pos->y_min -= pos->y_max - pos->y_lastc + line_sup - 1;
	if (curr)
		move_pos(pos, curr->len);
	else
		move_pos(pos, ft_strlen(*str));
}

void		termcaps_history_prev(char **str, t_cursor_pos *pos
		, t_history_info *histo)
{
	size_t		i;
	t_history	*curr;

	if (!histo->history || !*histo->history || histo->history_line == 0)
		return ;
	curr = NULL;
	if (str)
		free(*str);
	histo->history_line--;
	if (histo->history_line == 0)
		*str = histo->first_command ? ft_strdup(histo->first_command)
			: ft_strdup("");
	else
	{
		curr = *histo->history;
		i = 0;
		while (++i < histo->history_line && curr->next)
			curr = curr->next;
		*str = ft_strdup(curr->str);
	}
	new_pos(str, curr, pos);
}
