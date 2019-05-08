/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 11:24:47 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/07 18:25:20 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		close_here_docs(t_redirect *redir)
{
	while (redir)
	{
		if (redir->p[0] > -1)
			close(redir->p[0]);
		if (redir->p[1] > -1)
			close(redir->p[1]);
		redir = redir->next;
	}
}

static void	write_doc(int p[], char **str)
{
	int		fd[2];

	if (pipe(fd) == -1)
		return ;
	write(fd[1], *str, ft_strlen(*str));
	p[0] = fd[0];
	p[1] = fd[1];
	close(fd[1]);
	ft_strdel(str);
}

void		get_here_doc(t_redirect *redir, t_shell *shell)
{
	char	*buf;
	char	*res;

	res = ft_strnew(0);
	g_ignore_signals = 3;
	while (redir && redir->type == TOKEN_REDIRI && redir->append)
	{
		while (g_ignore_signals && (get_input(0, &buf, shell) || 1))
		{
			if (!buf)
			{
				ft_putchar('\n');
				break ;
			}
			else if (ft_strcmp(buf, redir->value->content) == 0)
				break ;
			res = ft_strjointf(res, buf, ft_strdup("\n"));
		}
		write_doc(redir->p, &res);
		redir = redir->next;
	}
	g_ignore_signals = 0;
	ft_strdel(&res);
}

void		apply_here_doc(t_redirect *redir)
{
	dup2(redir->p[0], 0);
	close(redir->p[0]);
	close(redir->p[1]);
}
