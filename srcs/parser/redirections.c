/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:27:23 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/30 15:53:14 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		redirect_output(t_redirect *redir)
{
	int		fd;
	int		otype;

	otype = O_WRONLY | O_CREAT;
	otype |= (redir->append) ? O_APPEND : O_TRUNC;
	if ((fd = open(redir->value->content, otype, FILE_PERM)) == -1)
		return ;
	dup2(fd, redir->filedes);
	close(fd);
}

static void		redirect_input(t_redirect *redir)
{
	int		fd;
	int		otype;

	if ((fd = open(redir->value->content, O_RDONLY)) == -1)
		return ;
	dup2(fd, redir->filedes);
	close(fd);
}

void			handle_redirections(t_redirect *redir, t_shell *shell)
{
	while (redir && redir->value)
	{
		if (redir->type == TOKEN_REDIRO)
			redirect_output(redir);
		else if (redir->type == TOKEN_REDIRI)
		{
			if (redir->append)
				apply_here_doc(redir);
			else
				redirect_input(redir);
		}
		else if (redir->type == TOKEN_AGGR)
		{
			if (ft_strequ(redir->value->content, "-"))
				close(redir->filedes);
			else if (ft_isdigit(redir->value->content[0]))
				dup2(ft_atoi(redir->value->content), redir->filedes);
		}
		redir = redir->next;
	}
}
