/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_delete.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:32:13 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/02 15:38:26 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_char(char **str, t_cursor_pos *pos)
{
	char *l;
	char *r;

	l = ft_strndup(*str, pos->x_rel - 1);
	r = ft_strdup(*str + pos->x_rel);
	*str = ft_strfjoin(l, r, *str);
	free(l);
	free(r);
}

void	replace_lastc(t_cursor_pos *pos)
{
	if (pos->x_lastc == 0)
	{
		--(pos->y_lastc);
		pos->x_lastc = pos->x_max;
	}
	else
		--(pos->x_lastc);
}

int		termcaps_delete(char **str, t_cursor_pos *pos)
{
	if (pos->x > pos->x_min || (pos->y > pos->y_min && pos->x > 0))
	{
		tputs(tgetstr("le", NULL), 1, my_putchar);
		tputs(tgetstr("dc", NULL), 1, my_putchar);
		if (pos->y_lastc > pos->y)
		{
			tputs(tgoto(tgetstr("cm", NULL), 0, pos->y + 1), 1, my_putchar);
			tputs(tgetstr("cd", NULL), 1, my_putchar);
			if (pos->x_lastc > 0)
			{
				tputs(tgoto(tgetstr("cm", NULL), pos->x_max, pos->y), 1, my_putchar);
				ft_printf("%s", *str + pos->x_rel + (pos->x_max - pos->x) + 1);
			}
		}
		del_char(str, pos);
		--(pos->x);
		--(pos->x_rel);
		tputs(tgoto(tgetstr("cm", NULL), pos->x, pos->y), 1, my_putchar);
		replace_lastc(pos);	
	}
	else if (pos->y > pos->y_min && pos->x == 0)
	{
		//tputs(tgetstr("bw", NULL), 1, my_putchar);
		tputs(tgetstr("cd", NULL), 1, my_putchar);
		tputs(tgoto(tgetstr("cm", NULL), pos->x_max, pos->y - 1), 1, my_putchar);
		tputs(tgetstr("ce", NULL), 1, my_putchar);
		ft_printf("%s", *str + pos->x_rel);
		del_char(str, pos);
		pos->x = pos->x_max;
		--(pos->y);
		--(pos->x_rel);
		tputs(tgoto(tgetstr("cm", NULL), pos->x, pos->y), 1, my_putchar);
		//tputs(tgetstr("dc", NULL), 1, my_putchar);
		replace_lastc(pos);	
	}
	return (0);
}
