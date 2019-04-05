/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 19:16:48 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/04 17:19:46 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	final_position(t_cursor_pos *pos)
{
	if (pos->y_lastc == pos->y_max - 1)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, pos->y_lastc), 1, my_putchar);
		tputs(tgetstr("sf", NULL), 1, my_putchar);
		tputs(tgoto(tgetstr("cm", NULL), 0, pos->y_lastc), 1, my_putchar);
	}
	else
		tputs(tgoto(tgetstr("cm", NULL), 0, pos->y_lastc + 1), 1, my_putchar);
}
