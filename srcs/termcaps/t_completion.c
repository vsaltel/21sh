/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_completion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:43:39 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/16 14:31:48 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*actual_word(char *str, t_cursor_pos *pos)
{
	char	*res;
	size_t	i;
	size_t	j;

	res = NULL;
	i = pos->x_rel;
	while (i > 0 && str[i - 1] != ' ')
		i--;
	j = i;
	while (str[j] && str[j] != ' ')
		j++;
	res = ft_strndup(str + i, j - i);
	ft_printf("->|%s|\n", res);
	return (res);
}

static void	include_word(char *word, char **str, t_cursor_pos *pos)
{
	char	*left;
	char	*right;
	size_t	i;
	size_t	j;

	i = pos->x_rel;
	while (i > 0 && *str[i] != ' ')
		i--;
	left = ft_strndup(*str, i);
	j = i;
	while (*str[j] && *str[j] != ' ')
		j++;
	right = ft_strdup(*str + j);
	left = ft_strfjoin(left, word, left);
	left = ft_strfjoin(left, right, right);
	ft_strdel(str);
	*str = left;
	free(left);
	ft_printf("res =|%s|\n", *str);
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
	ft_printf("%s", str);
	pos->x = pos->x_min;
	pos->x_lastc = pos->x_min;
	pos->y = pos->y_min;
	pos->y_lastc = pos->y_min;
	pos->x_rel = 0;
	line_sup = (pos->x_lastc + 1 + len) / (pos->x_max + 1);
	if (line_sup + pos->y_lastc >= pos->y_max)
		pos->y_min -= pos->y_max - pos->y_lastc + line_sup - 1;
	move_pos(pos, len);
}

void		termcaps_completion(char **str, t_cursor_pos *pos, t_shell *shell)
{
	DIR		*dirp;
	struct dirent	*dirc;
	t_env	*path_env;
	char	**array;
	char	*word;
	int		i;

	if (!str || !*str)
		return ;
	word = actual_word(*str, pos);
	if ((path_env = get_enve(shell->env, "PATH")))
	{
		array = ft_strsplit(path_env->value, ':');
		i = -1;
		while (array[++i] != NULL)
			if ((dirp = opendir(array[i])))
			{
				while ((dirc = readdir(dirp)))
					if (ft_strncmp(word, dirc->d_name, ft_strlen(*str)) == 0)
					{
						include_word(word, str, pos);
						new_pos(*str, pos);
						closedir(dirp);
						ft_strddel(&array);
						free(word);
						return ;
					}
				closedir(dirp);
			}
	}
	free(word);
}
