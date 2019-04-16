/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_home.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:59:14 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/15 15:58:45 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		termcaps_home(char **str, t_cursor_pos *pos, t_history *histo)
{
	(void)histo;
	(void)str;
	tputs(tgoto(tgetstr("cm", NULL), pos->x_min, pos->y_min), 1, ft_putchar);
	pos->x = pos->x_min;
	pos->y = pos->y_min;
	pos->x_rel = 0;
}
