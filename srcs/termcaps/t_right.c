/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_right.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:34:17 by vsaltel           #+#    #+#             */
/*   Updated: 2019/05/08 15:32:17 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		termcaps_right(char **str, t_cursor_pos *pos, t_shell *shell)
{
	(void)shell;
	(void)str;
	if (!str || !*str)
		return ;
	if (pos->x_rel < (long)ft_strlen(*str))
		pos->x_rel++;
}
