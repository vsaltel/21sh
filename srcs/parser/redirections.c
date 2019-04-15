/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:27:23 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/15 16:46:45 by frossiny         ###   ########.fr       */
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

void			redirect_output(t_redirect *redir, t_files **files)
{
	int		fd;
	int		otype;

	otype = O_WRONLY | O_CREAT | O_TRUNC;
	if (redir->append)
		otype = O_WRONLY | O_APPEND | O_CREAT;
	fd = get_file_fd(*files, redir->value->content);
	if (fd == -1)
	{
		if ((fd = open(redir->value->content, otype, FILE_PERM)) == -1)
			return ;
		*files = create_file(*files, redir->value->content, redir->filedes);
		dup2(fd, redir->filedes);
		close(fd);
	}
	else
		dup2(fd, redir->filedes);
}

void			redirect_input(t_redirect *redir)
{
	int		fd;
	int		otype;

	if ((fd = open(redir->value->content, O_RDONLY)) == -1)
		return ;
	dup2(fd, redir->filedes);
	close(fd);
}

static void	get_here_doc(t_redirect *redir, t_shell *shell)
{
	/*int		ret;
	char	*buf;
	char	*res;
	int		fd[2];

	res = ft_strnew(0);
	write(1, "> ", 2);
	while ((ret = get_input(0, &buf, NULL)))
	{
		if (ft_strcmp(buf, redir->value->content) == 0)
			break ;
		res = ft_strjoint(res, buf, "\n");
		free(buf);
		write(1, "> ", 2);
	}
	if (pipe(fd) == -1)
		perror("21sh");
	write(fd[1], res, ft_strlen(res));
	dup2(fd[0], redir->filedes);
	close(fd[0]);
	close(fd[1]);
	ft_strdel(&res);*/
	ft_printf("Close %d\n", 0);
	dup2(redir->filedes, 0);
	ft_printf("Close %d\n", redir->filedes);
	close(redir->filedes);
}

void			handle_redirections(t_redirect *redir, t_shell *shell)
{
	t_files	*files;

	files = NULL;
	while (redir && redir->value)
	{
		if (redir->type == TOKEN_REDIRO)
			redirect_output(redir, &files);
		else if (redir->type == TOKEN_REDIRI)
		{
			if (redir->append)
				get_here_doc(redir, shell);
			else
				redirect_input(redir);
		}
		redir = redir->next;
	}
}
