/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_history_prev.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:57:50 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/18 11:40:45 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	new_pos(char **str, t_histo_lst *curr, t_cursor_pos *pos)
{
	size_t	line_sup;

	if (pos->y_lastc > pos->y_min)
	{
		move_cursor(0, pos->y_min + 1);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
	}
	move_cursor(pos->x_min, pos->y_min);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	ft_printf("%s", *str);
	line_sup = (pos->x_lastc + 1 + ft_strlen(*str)) / (pos->x_max + 1);
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
	if (curr)
		move_pos(pos, curr->len);
	else
		move_pos(pos, ft_strlen(*str));
}

void		termcaps_history_prev(char **str, t_cursor_pos *pos
		, t_shell *shell)
{
	size_t		i;
	t_histo_lst	*curr;

	if (!shell->history.lst || shell->history.pos == 0)
		return ;
	curr = NULL;
	if (str)
		free(*str);
	shell->history.pos--;
	if (shell->history.pos == 0)
		*str = shell->history.first_command
			? ft_strdup(shell->history.first_command) : ft_strdup("");
	else
	{
		curr = shell->history.lst;
		i = 0;
		while (++i < shell->history.pos && curr->next)
			curr = curr->next;
		*str = ft_strdup(curr->str);
	}
	new_pos(str, curr, pos);
}
