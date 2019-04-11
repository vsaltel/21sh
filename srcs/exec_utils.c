/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:27:04 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/11 16:13:49 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*handle_absolute(char *name, int verbose)
{
	char	*file;

	file = NULL;
	file = ft_strdup(name);
	if (file && access(file, F_OK) != -1)
	{
		if (access(file, X_OK) == -1)
			verbose ? permission_denied(name) : 0;
		return (file);
	}
	verbose ? inexistant(name) : 0;
	if (file)
		free(file);
	return (NULL);
}

static char	*handle_relative(char *name, int verbose)
{
	char	*tmp;
	char	*file;

	tmp = getcwd(NULL, 0);
	if (!(file = ft_strjoint(tmp, "/", name)))
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	if (access(file, F_OK) != -1)
	{
		if (access(file, X_OK) == -1)
			verbose ? permission_denied(name) : 0;
		return (file);
	}
	free(file);
	verbose ? inexistant(name) : 0;
	return (NULL);
}

static char	*get_exe_path(t_env *env, char *name)
{
	t_env		*path;
	char		**dirs;
	size_t		i;
	char		*file;

	if (!(path = get_enve(env, "PATH")))
		return (NULL);
	if (ft_strcmp(path->value, "") == 0 && name[0] == '/')
		return (handle_absolute(name, 0));
	else if (ft_strcmp(path->value, "") == 0 && name[0] != '/')
		return (handle_relative(name, 0));
	i = -1;
	dirs = ft_strsplit(path->value, ':');
	while (dirs && dirs[++i])
	{
		file = format_path_exe(dirs[i], name);
		if (access(file, F_OK) == 0)
			break ;
		ft_strdel(&file);
	}
	ft_strddel(&dirs);
	if (file && access(file, F_OK) == 0)
		return (file);
	ft_strdel(&file);
	return (NULL);
}

char		*get_exe(t_env *env, char *name, int verbose)
{
	char		*file;
	struct stat	stats;

	file = NULL;
	if (name[0] == '/')
		return (handle_absolute(name, verbose));
	else if (is_relative_path(name))
		return (handle_relative(name, verbose));
	file = get_exe_path(env, name);
	if (file && stat(file, &stats) == 0)
		return (file);
	if (file)
		free(file);
	verbose ? not_found(name) : 0;
	return (NULL);
}

int			is_exe(t_env *env, char *name, int verbose)
{
	int		ret;
	char	*tmp;

	tmp = get_exe(env, name, verbose);
	ret = tmp != NULL;
	free(tmp);
	return (ret);
}
