/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_home.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:59:14 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/29 14:49:25 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		termcaps_home(char **str, t_cursor_pos *pos, t_shell *shell)
{
	(void)shell;
	(void)str;
	if (!str || !*str)
		return ;
	move_cursor(pos->x_min, pos->y_min);
	pos->x = pos->x_min;
	pos->y = pos->y_min;
	pos->x_rel = 0;
}
