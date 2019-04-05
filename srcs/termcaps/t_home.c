/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_home.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:59:14 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/05 16:05:13 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		termcaps_home(char **str, t_cursor_pos *pos)
{
	tputs(tgoto(tgetstr("cm", NULL), pos->x_min, pos->y_min), 1, my_putchar);
	pos->x = pos->x_min;
	pos->y = pos->y_min;
	pos->x_rel = 0;
	return (0);
}
