/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:03:28 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/15 14:55:46 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

const t_builtin g_builtins[] =
{
	{ "echo", &b_echo },
	{ "cd", &b_cd },
	{ "setenv", &b_setenv },
	{ "unsetenv", &b_unsetenv },
	{ "env", &b_env },
	{ "exit", &b_exit },
	{ NULL, NULL }
};

int					is_builtin(char *name)
{
	size_t	i;

	i = 0;
	if (!name)
		return (0);
	while (g_builtins[i].name)
	{
		if (ft_strcmp(name, g_builtins[i].name) == 0)
			return (1);
		i++;
	}
	return (0);
}

static t_builtin	get_builtin(char *name)
{
	const	t_builtin	nbuiltin = { NULL, NULL };
	size_t				i;

	i = 0;
	while (g_builtins[i].name)
	{
		if (ft_strcmp(name, g_builtins[i].name) == 0
												&& g_builtins[i].func)
			return (g_builtins[i]);
		i++;
	}
	return (nbuiltin);
}

static void			end_redir(int fd[])
{
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	dup2(fd[2], 2);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
}

int					handle_builtin(t_cmd *cmd, t_shell *shell)
{
	t_builtin	builtin;
	int			ret;
	int			fd[3];

	if (!cmd->exe->content)
		return (-1);
	if (!(builtin = get_builtin(cmd->exe->content)).func)
		return (-1);
	if (cmd->redir)
	{
		fd[0] = dup(0);
		fd[1] = dup(1);
		fd[2] = dup(2);
	}
	handle_redirections(cmd->redir);
	ret = builtin.func(cmd, shell);
	if (cmd->redir)
		end_redir(fd);
	return (ret);
}
