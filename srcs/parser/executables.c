/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:26:37 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/01 18:27:22 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	start_process(t_cmd *cmd, t_shell *shell)
{
	char	*file;
	int		status;

	if (!(file = get_exe(shell, cmd->exe->content, 1)) || access(file, X_OK))
		return (file ? 126 : 127);
	get_here_doc(cmd->redir);
	if ((g_child = fork()) == 0)
	{
		unregister_signals();
		restore_shell(shell->prev_term);
		cmd->redir ? handle_redirections(cmd->redir, shell) : 0;
		if (execve(file, cmd->args, build_env(shell->env)) == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	free(file);
	close_here_docs(cmd->redir);
	if (g_child == -1)
		return (g_child = 0);
	waitpid(g_child, &status, 0);
	termcaps_init(NULL);
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
