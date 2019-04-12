/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_end.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:01:57 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/12 11:32:35 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		termcaps_end(char **str, t_cursor_pos *pos, t_history_info *histo)
{
	(void)histo;
	tputs(tgoto(tgetstr("cm", NULL), pos->x_lastc, pos->y_lastc)
		, 1, ft_putchar);
	pos->x = pos->x_lastc;
	pos->y = pos->y_lastc;
	pos->x_rel = ft_strlen(*str);
	return ;
}
