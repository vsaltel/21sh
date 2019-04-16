/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_right_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:58:58 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/16 18:14:10 by vsaltel          ###   ########.fr       */
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
	pos->x_rel++;
	pos->x++;
	if (pos->x > pos->x_max)
	{
		pos->x = 0;
		pos->y++;
	}
}

void			termcaps_right_word(char **str, t_cursor_pos *pos
		, t_shell *shell)
{
	(void)shell;
	if (!str || !*str)
		return ;
	while ((*str)[pos->x_rel] && !is_delimiter(*str + pos->x_rel))
		maj_pos(pos);
	while ((*str)[pos->x_rel] && is_delimiter(*str + pos->x_rel))
		maj_pos(pos);
	move_cursor(pos->x, pos->y);
}
