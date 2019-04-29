/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_down.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:57:00 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/29 14:49:09 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	termcaps_down(char **str, t_cursor_pos *pos, t_shell *shell)
{
	(void)shell;
	if (!str || !*str)
		return ;
	if ((pos->y == pos->y_lastc - 1 && pos->x <= pos->x_lastc)
		|| (pos->y < pos->y_lastc - 1))
	{
		pos->y++;
		pos->x_rel += pos->x_max + 1;
		move_cursor(pos->x, pos->y);
	}
	else if (pos->y == pos->y_lastc - 1 && pos->x > pos->x_lastc)
	{
		pos->y = pos->y_lastc;
		pos->x = pos->x_lastc;
		pos->x_rel = ft_strlen(*str);
		move_cursor(pos->x, pos->y);
	}
}
