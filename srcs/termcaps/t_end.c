/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_end.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:01:57 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/16 18:13:26 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		termcaps_end(char **str, t_cursor_pos *pos, t_shell *shell)
{
	(void)shell;
	move_cursor(pos->x_lastc, pos->y_lastc);
	pos->x = pos->x_lastc;
	pos->y = pos->y_lastc;
	pos->x_rel = ft_strlen(*str);
	return ;
}
