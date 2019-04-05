/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_end.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:01:57 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/05 16:06:35 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		termcaps_end(char **str, t_cursor_pos *pos)
{
	tputs(tgoto(tgetstr("cm", NULL), pos->x_lastc, pos->y_lastc), 1, my_putchar);
	pos->x = pos->x_lastc;
	pos->y = pos->y_lastc;
	pos->x_rel = ft_strlen(*str);
	return (0);
}
