/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:26:37 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/10 14:59:41 by frossiny         ###   ########.fr       */
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

int				execute(t_cmd *cmd, t_env **env, t_lexer *lex)
{
	int		ret;
	char	*path;
	char	**envp;

	if ((ret = handle_builtin(cmd, env, lex)) == -1)
	{
		envp = build_env(*env);
		path = get_exe(*env, cmd->exe->content, 1);
		ret = start_process(path, cmd->args, envp);
		free(path);
		ft_strddel(&envp);
	}
	return (ret);
}
