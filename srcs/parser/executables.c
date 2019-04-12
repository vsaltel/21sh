/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:26:37 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/12 18:11:07 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	start_process(t_cmd *cmd, t_env *env)
{
	char	*file;
	int		status;

	if (!(file = get_exe(env, cmd->exe->content, 1)) || access(file, X_OK))
		return (file ? 126 : 127);
	if ((g_child = fork()) == 0)
	{
		if (cmd->redir)
			handle_redirections(cmd->redir, 0);
		if (execve(file, cmd->args, build_env(env)) == -1)
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
		ret = start_process(cmd, shell->env);
	return (ret);
}

int			execute(t_cmd *cmd, t_shell *shell)
{
	build_args(cmd, shell);
	cmd->redir = parse_redirections(cmd->exe, cmd->argc);
	return (start(cmd, shell));
}
