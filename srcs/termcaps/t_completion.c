/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_completion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:43:39 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/29 14:58:21 by vsaltel          ###   ########.fr       */
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

static void	include_word(char *word, char **str, t_cursor_pos *pos)
{
	char	*left;
	char	*right;
	size_t	i;
	size_t	j;
	size_t	tmp;

	i = pos->x_rel;
	pos->o_input = *str;
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
	*str = ft_strfjoin(left, right, right);
}

static void	new_pos(char *str, t_cursor_pos *pos)
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
	move_pos(pos, len, len);
}

int		complete_path(char **str, char *word, t_cursor_pos *pos, t_shell *shell, int *index)
{
	DIR				*dirp;
	struct dirent	*dirc;
	t_env			*path_env;
	char			**array;
	int				i;

	if ((path_env = get_enve(shell->env, "PATH")))
	{
		array = ft_strsplit(path_env->value, ':');
		i = -1;
		while (array[++i] != NULL)
		{
			if ((dirp = opendir(array[i])))
			{
				while ((dirc = readdir(dirp)))
				{
					if (ft_strnequ(word, dirc->d_name, ft_strlen(word)))
					{
						if (*index == 0)
						{
							include_word(dirc->d_name, str, pos);
							new_pos(*str, pos);
							closedir(dirp);
							ft_strddel(&array);
							return (1);
						}
						else
							(*index)--;
					}
				}
				closedir(dirp);
			}
		}
		ft_strddel(&array);
	}
	return (0);
}

char	*get_path(char **word)
{
	size_t	i;

	i = ft_strlen(*word);
	while (i)
	{
		if ((*word)[i] == '/')
			return (ft_strndup(*word, i));
		i--;
	}
	return (ft_strdup("."));
}

size_t		get_file_start(char *word)
{
	size_t	i;

	i = ft_strlen(word);
	while (i)
	{
		if (word[i] == '/')
			return (i + 1);
		i--;
	}
	return (0);
}

int		complete_files(char **str, char *word, t_cursor_pos *pos, t_shell *shell, int *index)
{
	DIR				*dirp;
	struct dirent	*dirc;
	char			*path;
	char			*file;

	path = get_path(&word);
	file = word + get_file_start(word);
	if ((dirp = opendir(path)))
	{
		while ((dirc = readdir(dirp)))
		{
			if (dirc->d_name[0] != '.')
			{
				if (ft_strnequ(dirc->d_name, file, ft_strlen(file)))
				{
					if (index == 0)
					{
						include_word(ft_strequ(path, ".") ? dirc->d_name : ft_strjoint(path, "/", dirc->d_name), str, pos);
						new_pos(*str, pos);
						closedir(dirp);
						free(path);
						return (1);
					}
					else
						(*index)--;
				}
			}
		}
		closedir(dirp);
	}
	free(path);
	return (0);
}

int		complete_builtins(char **str, char *word, t_cursor_pos *pos, t_shell *shell, int *index)
{
	char	*curr;
	int		i;

	i = -1;
	while (g_builtins_c[++i])
	{
		if (ft_strnequ(word, g_builtins_c[i], ft_strlen(word)))
		{
			if (index == 0)
			{
				include_word((char *)g_builtins_c[i], str, pos);
				new_pos(*str, pos);
				return (1);
			}
		}
	}
	return (0);
}

void		termcaps_completion(char **str, t_cursor_pos *pos, t_shell *shell)
{
	char	*word;
	int		index;

	if (!str || !*str || ft_strlen(*str) < 1)
		return ;
	index = pos->compl;
	if (index > 0 && pos->o_input)
	{
		ft_strdel(str);
		*str = ft_strdup(pos->o_input);
		pos->x_rel = pos->opos;
	}
	word = actual_word(*str, pos);
	if (!complete_builtins(str, word, pos, shell, &index))
		if(!complete_files(str, word, pos, shell, &index))
			if (!complete_path(str, word, pos, shell, &index))
			{
				pos->compl = 0;
				free(word);
				return ;
			}
	free(word);
	pos->compl++;
}
