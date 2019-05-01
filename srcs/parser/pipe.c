/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:32:11 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/01 15:55:43 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

static void	close_fd(int fd[])
{
	close(fd[0]);
	close(fd[1]);
}

static int	execute_pipe_cmd(t_pipel *pline, int op[], int np[], t_shell *shell)
{
	t_cmd	*cmd;

	cmd = pline->cmd;
	if ((pline->previous && is_builtin(cmd->exe->content))
							|| !is_exe(shell, cmd->exe->content, 1))
		return (1);
	if ((g_child = fork()) == 0)
	{
		restore_shell(shell->prev_term);
		init_fd(pline, op, np, shell);
		if (execve(get_exe(shell, cmd->exe->content, 1),
								cmd->args, build_env(shell->env)) == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else if (pline->previous)
		close_fd(op);
	return (0);
}

static void	copy_fd(int op[], int np[])
{
	op[0] = np[0];
	op[1] = np[1];
}

int			execute_pipes(t_anode *node, t_shell *shell, t_anode **cn)
{
	int		op[2];
	int		np[2];
	t_pipel	*pipeline;
	int		ret;

	pipeline = build_pipeline(node, shell, cn);
	while (pipeline && pipeline->cmd)
	{
		if (pipeline->next)
			pipe(np);
		get_here_doc(pipeline->cmd->redir);
		execute_pipe_cmd(pipeline, op, np, shell);
		if (pipeline->next)
			copy_fd(op, np);
		if (!pipeline->next)
			break ;
		pipeline = pipeline->next;
	}
	waitpid(g_child, &ret, 0);
	g_return = WIFSIGNALED(ret) ? 128 + ret : ret;
	del_pipeline(pipeline);
	g_child = 0;
	termcaps_init(NULL);
	return (g_return);
}
