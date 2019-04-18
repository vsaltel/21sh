/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_history_next.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:58:32 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/18 14:28:39 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	new_pos(t_histo_lst *curr, t_cursor_pos *pos)
{
	size_t	line_sup;

	if (pos->y_lastc > pos->y_min)
	{
		move_cursor(0, pos->y_min + 1);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
	}
	move_cursor(pos->x_min, pos->y_min);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	ft_printf("%s", curr->str);
	line_sup = (pos->x_lastc + 1 + curr->len) / (pos->x_max + 1);
	if (line_sup + pos->y_lastc >= pos->y_max)
	{
		pos->y_min -= pos->y_max - pos->y_lastc + line_sup - 1;
		pos->y_lastc -= pos->y_max - pos->y_lastc + line_sup - 1;
	}
	pos->x = pos->x_min;
	pos->x_lastc = pos->x_min;
	pos->y = pos->y_min;
	pos->y_lastc = pos->y_min;
	pos->x_rel = 0;
	move_pos(pos, curr->len);
}

void		termcaps_history_next(char **str, t_cursor_pos *pos
		, t_shell *shell)
{
	size_t		i;
	t_histo_lst	*curr;

	if (!shell->history.lst || shell->history.pos == shell->history.size)
		return ;
	if (shell->history.pos < shell->history.size)
		shell->history.pos++;
	curr = shell->history.lst;
	i = 0;
	while (++i < shell->history.pos && curr->next)
		curr = curr->next;
	new_pos(curr, pos);
	if (shell->history.pos == 1 && *str)
	{
		if (shell->history.first_command)
			ft_strdel(&(shell->history.first_command));
		shell->history.first_command = ft_strdup(*str);
	}
	if (str)
		free(*str);
	*str = ft_strdup(curr->str);
}
