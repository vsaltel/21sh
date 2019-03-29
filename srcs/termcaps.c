/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:02:25 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/29 18:20:27 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		termcaps_delete(char **str, t_cursor_pos *pos)
{
	char *l;
	char *r;

	if (pos->x > pos->x_min || (pos->y > pos->y_min && pos->x > 0))
	{
		l = ft_strndup(*str, pos->x_rel - 1);
		r = ft_strdup(*str + pos->x_rel);
		*str = ft_strfjoin(l, r, *str);
		free(l);
		free(r);
		tputs(tgetstr("le", NULL), 1, my_putchar);
		tputs(tgetstr("dc", NULL), 1, my_putchar);
		--(pos->x);
		--(pos->x_rel);
		if (pos->x_lastc == 0)
		{
			--(pos->y_lastc);
			pos->x_lastc = pos->x_max;
		}
		else
			--(pos->x_lastc);
	}
	else if (pos->y > pos->y_min && pos->x == 0)
	{
		/*
		l = ft_strndup(*str, pos->x_max);
		r = ft_strdup(*str + pos->x);
		*str = ft_strfjoin(l, r, *str);
		free(l);
		free(r);
		*/
		tputs(tgetstr("bw", NULL), 1, my_putchar);
		tputs(tgetstr("dc", NULL), 1, my_putchar);
		--(pos->y);
		--(pos->x_rel);
		pos->x = pos->x_max;
		if (pos->x_lastc == 0)
		{
			--(pos->y_lastc);
			pos->x_lastc = pos->x_max;
		}
		else
			--(pos->x_lastc);
	}
	return (0);
}

int		termcaps_left(char **str, t_cursor_pos *pos)
{
	if (pos->x > pos->x_min || (pos->y > pos->y_min && pos->x > 0))
	{
		tputs(tgetstr("le", NULL), 1, my_putchar);
		--(pos->x);
		--(pos->x_rel);
	}
	else if (pos->y > pos->y_min && pos->x == 0)
	{
		tputs(tgetstr("bw", NULL), 1, my_putchar);
		pos->x = pos->x_max;
		--(pos->y);
		--(pos->x_rel);
	}
	return (0);
}

int		termcaps_right(char **str, t_cursor_pos *pos)
{
	if ((pos->x < pos->x_lastc || (pos->y < pos->y_lastc && pos->x < pos->x_max)) || (pos->y < pos->y_lastc && pos->x < pos->x_max))
	{
		//ft_printf("posx %d posxlastc %d posy %d posylastc %d posxmax %d posymax %d", pos->x, pos->x_lastc, pos->y, pos->y_lastc, pos->x_max, pos->y_max);
		tputs(tgetstr("nd", NULL), 1, my_putchar);
		++(pos->x);
		++(pos->x_rel);
	}
	else if (pos->y < pos->y_lastc && pos->x == pos->x_max)
	{
		tputs(tgoto(tgetstr("cm", NULL), (pos->x = 0), ++(pos->y)), 1, my_putchar);
		++(pos->x_rel);
	}
	return (0);
}

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
