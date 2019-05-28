/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:32:11 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/28 16:05:02 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell.h"

static void	init_fd(t_pipel *pline, int op[], int np[])
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
	handle_redirections(pline->cmd->redir);
}

static int	execute_pipe_builtin(t_pipel *pline, int op[], int np[], t_shell *shell)
{
	t_builtin	builtin;
	t_cmd		*cmd;
	int			ret;

	cmd = pline->cmd;
	if (!(builtin = get_builtin(cmd->exe->content)).func)
		return (-1);
	init_fd(pline, op, np);
	ret = builtin.func(cmd, shell);
	if (pline->previous)
	{
		close(op[0]);
		close(op[1]);
	}
	return (ret);
}

static int	execute_pipe_cmd(t_pipel *pline, int op[], int np[], t_shell *shell)
{
	t_cmd	*cmd;
	int		ret;

	cmd = pline->cmd;
	if ((ret = can_execute(cmd->exe->content, shell)))
		return (ret);
	if ((g_child = fork()) == 0)
	{
		unregister_signals();
		shell->able_termcaps ? restore_shell(shell->prev_term) : 0;
		init_fd(pline, op, np);
		if (execve(get_exe(shell, cmd->exe->content, 1),
								cmd->args, build_env(shell->env)) == -1)
			exit(EXIT_FAILURE);
	}
	else if (pline->previous)
	{
		close(op[0]);
		close(op[1]);
	}
	return (ret);
}

static void	copy_fd(int op[], int np[])
{
	op[0] = np[0];
	op[1] = np[1];
}

static void	end_pipes(int pid, int sfd[], t_shell *shell)
{
	int		ret;

	waitpid(pid, &ret, 0);
	if (pid > 0 && !g_return)
		g_return = WIFSIGNALED(ret) ? display_signal(ret) : WEXITSTATUS(ret);
	shell->able_termcaps ? termcaps_init(NULL) : 0;
	g_child = 0;
	ft_printf("Restore: %d -> %d\n", sfd[1], 1);
	dup2(sfd[0], 0);
	dup2(sfd[1], 1);
	close(sfd[0]);
	close(sfd[1]);
}

int			execute_pipes(t_anode *node, t_shell *shell, t_anode **cn)
{
	int		op[2];
	int		np[2];
	int		sfd[3];
	t_pipel	*pipeline;

	if (!(pipeline = build_pipeline(node, shell, cn)))
		return (1);
	sfd[0] = dup(0);
	sfd[1] = dup(1);
	while (pipeline && pipeline->cmd)
	{
		if (pipeline->next)
			pipe(np);
		get_here_doc(pipeline->cmd->redir, shell);
		g_return = is_builtin(pipeline->cmd->exe->content) ? execute_pipe_builtin(pipeline, op, np, shell) : execute_pipe_cmd(pipeline, op, np, shell);
		if (pipeline->next)
			copy_fd(op, np);
		if (!pipeline->next)
			break ;
		pipeline = pipeline->next;
	}
	end_pipes(g_child, sfd, shell);
	del_pipeline(pipeline);
	return (g_return);
}
