/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_completion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:43:39 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/30 15:03:35 by frossiny         ###   ########.fr       */
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

	i = pos->x_rel;
	if (pos->o_input)
		free(pos->o_input);
	pos->o_input = ft_strdup(*str);
	pos->opos = pos->x_rel;
	while (i > 0 && !ft_isspace((*str)[i - 1]))
		i--;
	left = ft_strndup(*str, i);
	pos->x_rel = i + ft_strlen(word);
	j = i;
	while ((*str)[j] && !ft_isspace((*str)[j]))
		j++;
	right = ft_strdup(*str + j);
	left = ft_strfjoin(left, word, left);
	ft_strdel(str);
	*str = ft_strfjoin(left, right, right);
	ft_strdel(&left);
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
				return (1);
			}
		}
	}
	return (0);
}

void		termcaps_completion(char **str, t_cursor_pos *pos, t_shell *shell)
{
	t_compl_info	ci;

	if (pos->visual_mode || !str || !*str || !ft_strlen(*str))
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
	if (ft_strcmp(ci.word, ""))
		if (!complete_builtins(&ci))
			if (!complete_files(&ci))
				if (!complete_path(&ci, shell))
				{
					ci.pos->compl = 0;
					free(ci.word);
					return ;
				}
	free(ci.word);
	pos->compl++;
}
