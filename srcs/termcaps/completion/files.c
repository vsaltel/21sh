/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:58:08 by frossiny          #+#    #+#             */
/*   Updated: 2019/08/12 18:27:33 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft.h"
#include "shell.h"

static char		*get_path(char *word, t_env *env)
{
	char	*search;

	if (word[0] == '~')
		return (get_tilde(word, env));
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
		return (word[0] == '~' ? word + 1 : word);
	return (search + 1);
}

static char		*get_home_word(char *word, char *dname)
{
	char	*file;
	char	*tmp;

	if (!(file = get_file_start(word)))
		return (NULL);
	if (!(tmp = ft_strndup(word, file - word)))
		return (NULL);
	word = ft_strjoin(tmp, dname);
	free(tmp);
	return (word);
}

static int		complete_file(char **str,
									char *dname, t_compl_info *ci, t_env *env)
{
	char			*tmp;
	char			*path;
	char			*word;
	t_cursor_pos	*pos;

	word = ci->word;
	pos = ci->pos;
	if (!(path = get_path(word, env)))
		return (0);
	if (word[0] == '~')
		tmp = get_home_word(word, dname);
	else if (path[ft_strlen(path) - 1] == '/')
		tmp = ft_strjoin(path, dname);
	else if (ft_strnequ(word, ".", 1) || ft_strcmp(path, "."))
		tmp = ft_strjoint(path, "/", dname);
	else
		tmp = ft_strdup(dname);
	include_word(tmp, str, pos);
	free(tmp);
	free(path);
	return (1);
}

int				complete_files(t_compl_info *ci, t_shell *shell)
{
	DIR				*dirp;
	struct dirent	*dirc;
	char			*file;
	char			*path;

	file = get_file_start(ci->word);
	path = get_path(ci->word, shell->env);
	(dirp = opendir(path)) ? free(path) : free(path);
	if (!dirp)
		return (0);
	while ((dirc = readdir(dirp)))
		if (dirc->d_name[0] != '.')
			if (ft_strnequ(dirc->d_name, file, ft_strlen(file)))
			{
				if (ci->index == 0)
				{
					complete_file(ci->str, dirc->d_name, ci, shell->env);
					closedir(dirp);
					return (1);
				}
				else
					ci->index--;
			}
	closedir(dirp);
	return (0);
}
