/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:58:08 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/07 18:22:49 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*get_path(char *word)
{
	char	*search;
	size_t	i;

	if (ft_strequ(word, "/"))
		return (ft_strdup("/"));
	if (!(search = ft_strrchr(word, '/')))
		return (ft_strdup("."));
	return (ft_strndup(word, search - word + 1));
}

static char		*get_file_start(char *word)
{
	char	*search;

	if (!(search = ft_strrchr(word, '/')))
		return (word);
	return (search + 1);
}

static int		complete_file(char **str, char *word,
										struct dirent *dirc, t_cursor_pos *pos)
{
	char	*tmp;
	char	*path;

	if (!(path = get_path(word)))
		return (0);
	if (path[ft_strlen(path) - 1] == '/')
		tmp = ft_strjoin(path, dirc->d_name);
	else if (ft_strnequ(word, ".", 1) || ft_strcmp(path, "."))
		tmp = ft_strjoint(path, "/", dirc->d_name);
	else
		tmp = dirc->d_name;
	include_word(tmp, str, pos);
	(ft_strnequ(word, ".", 1) || ft_strcmp(path, ".")) ? free(tmp) : 0;
	free(path);
	return (1);
}

int				complete_files(t_compl_info *ci)
{
	DIR				*dirp;
	struct dirent	*dirc;
	char			*file;
	char			*path;

	file = get_file_start(ci->word);
	path = get_path(ci->word);
	(dirp = opendir(path)) ? free(path) : free(path);
	if (!dirp)
		return (0);
	while ((dirc = readdir(dirp)))
		if (dirc->d_name[0] != '.')
			if (ft_strnequ(dirc->d_name, file, ft_strlen(file)))
			{
				if (ci->index == 0)
				{
					complete_file(ci->str, ci->word, dirc, ci->pos);
					closedir(dirp);
					return (1);
				}
				else
					ci->index--;
			}
	closedir(dirp);
	return (0);
}
