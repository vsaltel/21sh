/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_left_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:58:46 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/29 14:11:27 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		is_delimiter(char *str)
{
	size_t	i;

	i = 0;
	while (g_tokens_list + i && (g_tokens_list[i]).op)
	{
		if (ft_strncmp(g_tokens_list[i].op, str, 1) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void		maj_pos(t_cursor_pos *pos)
{
	pos->x_rel--;
	pos->x--;
	if ((long)pos->x < 0)
	{
		pos->x = pos->x_max;
		pos->y--;
	}
}

void			termcaps_left_word(char **str, t_cursor_pos *pos
		, t_shell *shell)
{
	(void)shell;
	if (!str || !*str)
		return ;
	if (pos->x_rel > 0 && !is_delimiter(*str + pos->x_rel))
		maj_pos(pos);
	while (pos->x_rel > 0 && is_delimiter(*str + pos->x_rel))
		maj_pos(pos);
	while (pos->x_rel > 0 && !is_delimiter(*str + pos->x_rel - 1))
		maj_pos(pos);
	move_cursor(pos->x, pos->y);
}
