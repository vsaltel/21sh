/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:27:23 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/12 18:12:48 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_files	*create_file(t_files *files, char *path, int fd)
{
	t_files *new;

	if (fd < 0 || !(new = (t_files *)malloc(sizeof(t_files))))
		return (NULL);
	new->path = path;
	new->fd = fd;
	new->next = files;
	return (new);
}

static int		get_file_fd(t_files *files, char *name)
{
	if (!files || !name)
		return (-1);
	while (files)
	{
		if (ft_strequ(files->path, name))
			return (files->fd);
		files = files->next;
	}
	return (-1);
}

void			handle_redirections(t_redirect *redir, int pipe)
{
	int		fd;
	int		otype;
	t_files	*files;

	files = NULL;
	while (redir && redir->value)
	{
		otype = O_WRONLY | O_CREAT | O_TRUNC;
		if (redir->append)
			otype = O_WRONLY | O_APPEND | O_CREAT;
		fd = get_file_fd(files, redir->value->content);
		if (fd == -1)
		{
			if ((fd = open(redir->value->content, otype, FILE_PERM)) == -1)
				return ;
			files = create_file(files, redir->value->content, redir->filedes);
			ft_printf("dup: %d\n", dup2(fd, redir->filedes));
			ft_printf("Closing %d\n", fd);
			close(fd);
		}
		else
			dup2(fd, redir->filedes);
		redir = redir->next;
	}
}
