/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_left.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:33:37 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/02 16:08:50 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		termcaps_left(char **str, t_cursor_pos *pos)
{
	//ft_printf("pos-y= %d pos-ymin= %d ",pos->y, pos->y_min);
	if (pos->x > pos->x_min || (pos->y > pos->y_min && pos->x > 0))
	{
		tputs(tgetstr("le", NULL), 1, my_putchar);
		pos->x--;
		pos->x_rel--;
	}
	else if (pos->y > pos->y_min && pos->x == 0)
	{
		//tputs(tgetstr("bw", NULL), 1, my_putchar);
		pos->x = pos->x_max;
		pos->y--;
		pos->x_rel--;
		tputs(tgoto(tgetstr("cm", NULL), pos->x, pos->y), 1, my_putchar);
	}
	return (0);
}
