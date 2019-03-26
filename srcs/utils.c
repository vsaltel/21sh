/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 12:46:01 by frossiny          #+#    #+#             */
/*   Updated: 2019/03/14 11:26:39 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*format_path_exe(char *dir, char *file)
{
	char	*path;

	path = NULL;
	if (dir[ft_strlen(dir) - 1] != '/')
		path = ft_strjoint(dir, "/", file);
	else
		path = ft_strjoin(dir, file);
	return (path);
}

int		is_local_exe(char *name)
{
	if (ft_strlen(name) > 1 && name[0] == '.' && name[1] == '/')
		return (1);
	if (ft_strlen(name) > 2 && name[0] == '.' && name[1] == '.'
													&& name[2] == '/')
		return (1);
	return (0);
}

int		is_relative_path(char *name)
{
	while (*name)
	{
		if (*name == '/')
			return (1);
		name++;
	}
	return (0);
}

int		cd_is_dir(char *file, char *name)
{
	struct stat stats;

	if (stat(file, &stats) == -1)
		return (0);
	if (!S_ISDIR(stats.st_mode))
	{
		write(2, "cd: not a directory: ", 21);
		ft_putstr_fd(name, 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	return (1);
}
