/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:32:11 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/15 16:49:53 by frossiny         ###   ########.fr       */
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

void		init_fd(t_pipel *pline, int op[], int np[], t_shell *shell)
{
	if (pline->previous)
	{
		dup2(op[0], 0);
		close(op[0]);
		close(op[1]);
	}
	if (pline->next)
	{
		close(np[0]);
		dup2(np[1], 1);
		close(np[1]);
	}
	handle_redirections(pline->cmd->redir, shell);
}

static int	execute_pipe_cmd(t_pipel *pline, int op[], int np[], t_shell *shell)
{
	int		pid;
	t_cmd	*cmd;
	int		ret;

	cmd = pline->cmd;
	if ((pline->previous && is_builtin(cmd->exe->content))
							|| !is_exe(shell->env, cmd->exe->content, 1))
		return (1);
	if ((pid = fork()) == 0)
	{
		init_fd(pline, op, np, shell);
		if (execve(get_exe(shell->env, cmd->exe->content, 1),
								cmd->args, build_env(shell->env)) == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else if (pline->previous)
	{
		close(op[0]);
		close(op[1]);
	}
	g_child = pid;
	waitpid(pid, &ret, 0);
	g_child = 0;
	if (WIFSIGNALED(ret))
		return (128 + ret);
	return (WEXITSTATUS(ret));
}

int			execute_pipes(t_anode *node, t_shell *shell, t_anode **cn)
{
	int		op[2];
	int		np[2];
	int		ret;
	t_pipel	*pipeline;

	ret = 0;
	pipeline = build_pipeline(node, shell, cn);
	while (pipeline && pipeline->cmd)
	{
		if (pipeline->next)
			pipe(np);
		get_here_doc(pipeline->cmd->redir);
		ret = execute_pipe_cmd(pipeline, op, np, shell);
		if (pipeline->next)
		{
			op[0] = np[0];
			op[1] = np[1];
		}
		if (!pipeline->next)
			break ;
		pipeline = pipeline->next;
	}
	del_pipeline(pipeline);
	return (ret);
}
