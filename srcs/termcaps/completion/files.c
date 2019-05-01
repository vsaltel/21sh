/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:58:08 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/26 15:14:44 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*get_path(char *word)
{
	size_t	i;

	i = ft_strlen(word);
	while (i)
	{
		if (word[i] == '/')
			return (ft_strndup(word, i));
		i--;
	}
	return (ft_strdup("."));
}

static size_t	get_file_start(char *word)
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

static int		complete_file(char **str, char *word,
										struct dirent *dirc, t_cursor_pos *pos)
{
	char	*tmp;
	char	*path;

	path = get_path(word);
	tmp = ft_strjoint(path, "/", dirc->d_name);
	if (ft_strnequ(word, ".", 1) || ft_strcmp(path, "."))
		tmp = ft_strjoint(path, "/", dirc->d_name);
	else
		tmp = dirc->d_name;
	include_word(tmp, str, pos);
	(ft_strnequ(word, ".", 1) || ft_strcmp(path, ".")) ? free(tmp) : 0;
	return (1);
}

int				complete_files(t_compl_info *ci)
{
	DIR				*dirp;
	struct dirent	*dirc;
	char			*file;

	file = ci->word + get_file_start(ci->word);
	if ((dirp = opendir(get_path(ci->word))))
	{
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
	}
	return (0);
}