/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_right.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:34:17 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/02 15:34:32 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		termcaps_right(char **str, t_cursor_pos *pos)
{
	if ((pos->x < pos->x_lastc || (pos->y < pos->y_lastc && pos->x < pos->x_max)) || (pos->y < pos->y_lastc && pos->x < pos->x_max))
	{
		//ft_printf("posx %d posxlastc %d posy %d posylastc %d posxmax %d posymax %d", pos->x, pos->x_lastc, pos->y, pos->y_lastc, pos->x_max, pos->y_max);
		tputs(tgetstr("nd", NULL), 1, my_putchar);
		++(pos->x);
		++(pos->x_rel);
	}
	else if (pos->y < pos->y_lastc && pos->x == pos->x_max)
	{
		tputs(tgoto(tgetstr("cm", NULL), (pos->x = 0), ++(pos->y)), 1, my_putchar);
		++(pos->x_rel);
	}
	return (0);
}
