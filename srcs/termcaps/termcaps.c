/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:02:25 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/15 15:57:47 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_ex_caps	search_caps(const char *s)
{
	const t_ex_caps	empty = {NULL, 1, NULL};
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

int					execute_termcaps(char *buf, char **str
		, t_cursor_pos *pos, t_history *histo)
{
	t_ex_caps termcaps;

	termcaps = search_caps(buf);
	if (!(termcaps.content))
		return (0);
	if (termcaps.func)
		termcaps.func(str, pos, histo);
	return (1);
}
