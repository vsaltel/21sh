/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_left_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:58:46 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/11 18:39:03 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static size_t	is_delimiter(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (g_tokens_list + i && (g_tokens_list[i]).op)
	{
		if (ft_strncmp(g_tokens_list[i].op, str, 1) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void		maj_pos(t_cursor_pos *pos, size_t len)
{
	pos->x_rel -= len;
	pos->x -= len;
	if ((long)pos->x < 0)
	{
		pos->x = pos->x_max - (len + 1);
		pos->y--;
	}
}

void			termcaps_left_word(char **str, t_cursor_pos *pos
		, t_history_info *histo)
{
	(void)histo;
	if (pos->x_rel > 0 && !is_delimiter(*str + pos->x_rel))
		maj_pos(pos, 1);
	while (pos->x_rel > 0 && is_delimiter(*str + pos->x_rel))
		maj_pos(pos, 1);
	while (pos->x_rel > 0 && !is_delimiter(*str + pos->x_rel - 1))
		maj_pos(pos, 1);
	tputs(tgoto(tgetstr("cm", NULL), pos->x, pos->y), 1, ft_putchar);
}
