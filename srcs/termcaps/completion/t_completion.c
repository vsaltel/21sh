/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_completion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:43:39 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/25 17:33:23 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const char *g_builtins_c[] =
{
	"echo",
	"cd",
	"setenv",
	"unsetenv",
	"env",
	"exit",
	NULL,
};

static char	*actual_word(char *str, t_cursor_pos *pos)
{
	char	*res;
	size_t	i;
	size_t	j;

	res = NULL;
	i = pos->x_rel;
	while (i > 0 && !ft_isspace(str[i - 1]))
		i--;
	j = i;
	while (str[j] && !ft_isspace(str[j]))
		j++;
	res = ft_strndup(str + i, j - i);
	return (res);
}

void		include_word(char *word, char **str, t_cursor_pos *pos)
{
	char	*left;
	char	*right;
	size_t	i;
	size_t	j;
	size_t	tmp;

	i = pos->x_rel;
	if (pos->o_input)
		free(pos->o_input);
	pos->o_input = ft_strdup(*str);
	pos->opos = pos->x_rel;
	tmp = ft_strlen(*str);
	while (i > 0 && (*str)[i] != ' ')
		i--;
	left = ft_strndup(*str, i);
	j = i;
	while ((*str)[j] && (*str)[j] != ' ')
		j++;
	right = ft_strdup(*str + j);
	left = ft_strfjoin(left, word, left);
	ft_strdel(str);
	*str = ft_strfjoin(left, right, right);
	ft_strdel(&left);
}

void		t_new_pos(char *str, t_cursor_pos *pos)
{
	size_t	line_sup;
	size_t	len;

	len = ft_strlen(str);
	if (pos->y_lastc > pos->y_min)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, pos->y_min + 1), 1, ft_putchar);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
	}
	tputs(tgoto(tgetstr("cm", NULL), pos->x_min, pos->y_min), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	write(1, str, ft_strlen(str));
	line_sup = (pos->x_lastc + 1 + len) / (pos->x_max + 1);
	if (line_sup + pos->y_lastc >= pos->y_max)
	{
		pos->y_min -= pos->y_max - pos->y_lastc + line_sup - 1;
		pos->y_lastc -= pos->y_max - pos->y_lastc + line_sup - 1;
	}
	pos->x = pos->x_min;
	pos->x_lastc = pos->x_min;
	pos->y = pos->y_min;
	pos->y_lastc = pos->y_min;
	pos->x_rel = 0;
	move_pos(pos, len);
}

static int	complete_builtins(t_compl_info *infos)
{
	char	*curr;
	int		i;

	i = -1;
	while (g_builtins_c[++i])
	{
		if (ft_strnequ(infos->word, g_builtins_c[i], ft_strlen(infos->word)))
		{
			if (infos->index == 0)
			{
				include_word((char *)g_builtins_c[i], infos->str, infos->pos);
				t_new_pos(*(infos->str), infos->pos);
				return (1);
			}
		}
	}
	return (0);
}

void		termcaps_completion(char **str, t_cursor_pos *pos, t_shell *shell)
{
	t_compl_info	ci;

	if (!str || !*str || !ft_strlen(*str))
		return ;
	ci.index = pos->compl;
	if (ci.index > 0 && pos->o_input)
	{
		free(*str);
		*str = ft_strdup(pos->o_input);
		pos->x_rel = pos->opos;
	}
	ci.str = str;
	ci.pos = pos;
	ci.word = actual_word(*str, pos);
	if (!complete_builtins(&ci))
		if (!complete_files(&ci))
			if (!complete_path(&ci, shell))
			{
				ci.pos->compl = 0;
				free(ci.word);
				!ci.index ? termcaps_completion(ci.str, ci.pos, shell) : 0;
				return ;
			}
	free(ci.word);
	pos->compl++;
}
