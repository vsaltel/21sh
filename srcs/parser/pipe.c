/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:32:11 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/11 13:44:00 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		init_fd(t_pipel *pline, int op[], int np[])
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
}

static int	execute_pipe_cmd(t_pipel *pline, int op[], int np[], t_env **env)
{
	int		pid;
	t_cmd	*cmd;
	int		ret;

	if ((pid = fork()) == 0)
	{
		init_fd(pline, op, np);
		cmd = pline->cmd;
		if (execve(get_exe(*env, cmd->exe->content, 1),
								cmd->args, build_env(*env)) == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else if (pline->previous)
	{
		close(op[0]);
		close(op[1]);
	}
	waitpid(pid, &ret, 0);
	return (WEXITSTATUS(ret));
}

int			execute_pipes(t_anode *node, t_env **env, t_lexer *lexer)
{
	int		op[2];
	int		np[2];
	int		ret;
	t_pipel	*pipeline;

	ret = 0;
	op[0] = -1;
	op[1] = -1;
	pipeline = build_pipeline(node);
	while (pipeline && pipeline->cmd)
	{
		if (pipeline->next)
			pipe(np);
		ret = execute_pipe_cmd(pipeline, op, np, env);
		if (pipeline->next)
		{
			op[0] = np[0];
			op[1] = np[1];
		}
		pipeline = pipeline->next;
	}
	del_pipeline(pipeline);
	return (ret);
}
