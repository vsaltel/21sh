/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:26:37 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/15 16:48:49 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


static void		get_here_doc(t_redirect *redir)
{
	int		ret;
	char	*buf;
	char	*res;
	int		fd[2];

	res = ft_strnew(0);
	while (redir && redir->value && redir->type == TOKEN_REDIRI && redir->append)
	{
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
			return ;
		ft_printf("Open: %d - %d\n", fd[0], fd[1]);
		write(fd[1], res, ft_strlen(res));
		redir->p[0] = fd[0];
		redir->p[1] = fd[1];
		redir->filedes = fd[0];
		ft_printf("Close %d\n", fd[1]);
		close(fd[1]);
		ft_strdel(&res);
		redir = redir->next;
	}
}

static int	start_process(t_cmd *cmd, t_shell *shell)
{
	char	*file;
	int		status;

	if (!(file = get_exe(shell->env, cmd->exe->content, 1)) || access(file, X_OK))
		return (file ? 126 : 127);
	get_here_doc(cmd->redir);
	if ((g_child = fork()) == 0)
	{
		if (cmd->redir)
			handle_redirections(cmd->redir, shell);
		if (execve(file, cmd->args, build_env(shell->env)) == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	free(file);
	if (g_child == -1)
		return (-1);
	waitpid(g_child, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + status);
	g_child = 0;
	return (WEXITSTATUS(status));
}

static int	start(t_cmd *cmd, t_shell *shell)
{
	int		ret;

	if ((ret = handle_builtin(cmd, shell)) == -1)
		ret = start_process(cmd, shell);
	return (ret);
}

int			execute(t_cmd *cmd, t_shell *shell)
{
	build_args(cmd, shell);
	cmd->redir = parse_redirections(cmd->exe, cmd->argc);
	return (start(cmd, shell));
}
