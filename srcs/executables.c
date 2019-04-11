/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:26:37 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/11 15:18:45 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		start_process(char *file, char **args, char **env)
{
	int		status;

	if (!file || access(file, X_OK))
		return (file ? 126 : 127);
	status = 0;
	g_child = fork();
	if (g_child == 0)
	{
		if (execve(file, args, env) == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	if (g_child == -1)
		return (-1);
	waitpid(g_child, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + status);
	g_child = 0;
	return (WEXITSTATUS(status));
}

static int		start(t_cmd *cmd, t_shell *shell)
{
	int		ret;
	char	*path;
	char	**envp;

	if ((ret = handle_builtin(cmd, shell)) == -1)
	{
		envp = build_env(shell->env);
		path = get_exe(shell->env, cmd->exe->content, 1);
		ret = start_process(path, cmd->args, envp);
		free(path);
		ft_strddel(&envp);
	}
	return (ret);
}

int			execute(t_cmd *cmd, t_shell *shell)
{
	build_args(cmd, shell);
	return (start(cmd, shell));
}
