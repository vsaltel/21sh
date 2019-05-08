/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:26:37 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/07 18:40:13 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	start_process(char *file, t_cmd *cmd, t_env *env, t_shell *shell)
{
	int		status;

	get_here_doc(cmd->redir, shell);
	if ((g_child = fork()) == 0)
	{
		unregister_signals();
		shell->able_termcaps ? restore_shell(shell->prev_term) : 0;
		handle_redirections(cmd->redir, shell);
		handle_aggregate(cmd->redir, shell);
		if (execve(file, cmd->args, build_env(env)) == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	close_here_docs(cmd->redir);
	if (g_child == -1)
		return (g_child = 0);
	waitpid(g_child, &status, 0);
	shell->able_termcaps ? termcaps_init(NULL) : 0;
	g_child = 0;
	if (WIFSIGNALED(status))
		return (128 + status);
	return (WEXITSTATUS(status));
}

static int	start(t_cmd *cmd, t_env *env, t_shell *shell)
{
	int		ret;
	char	*file;

	if (!cmd->allow_builtins || (ret = handle_builtin(cmd, shell)) == -1)
	{
		if (!(file = get_exe(shell, cmd->exe->content, 1)))
			return (127);
		if (access(file, X_OK))
		{
			permission_denied(file);
			free(file);
			return (126);
		}
		ret = start_process(file, cmd, env, shell);
		free(file);
	}
	return (ret);
}

int			execute(t_cmd *cmd, t_shell *shell)
{
	build_args(cmd, shell->env);
	cmd->redir = parse_redirections(cmd->exe, cmd->argc);
	return (start(cmd, shell->env, shell));
}

int			execute_env(t_cmd *cmd, t_env *env, t_shell *shell)
{
	build_args(cmd, env);
	cmd->redir = parse_redirections(cmd->exe, cmd->argc);
	return (start(cmd, env, shell));
}
