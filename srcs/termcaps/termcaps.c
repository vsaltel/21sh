/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:02:25 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/03 14:47:55 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_ex_caps	search_caps(const char *s, t_cursor_pos *pos)
{
	const t_ex_caps	empty = {NULL, 1, CAPS_NULL};
	size_t			i;

	if (!s)
		return (empty);
	i = 0;
	while (g_caps_list + i && (g_caps_list[i]).content)
	{
		if (ft_strncmp(g_caps_list[i].content, s, g_caps_list[i].size) == 0)
			return (g_caps_list[i]);
		i++;
	}
	return (empty);
}

int		execute_termcaps(char *buf, char **str, t_cursor_pos *pos)
{
	t_ex_caps termcaps;

	termcaps = search_caps(buf, pos);
	if (!(termcaps.content))
		return (0);
	if (termcaps.type != CAPS_NULL)
		termcaps.func(str, pos);
	return (1);
}
