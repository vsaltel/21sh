/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:03:28 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/11 14:40:15 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		is_builtin(char *name)
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

int		handle_builtin(t_cmd *cmd, t_shell *shell)
{
	size_t	i;
	int		argc;
	char	**tmp;

	i = 0;
	if (!cmd->exe->content)
		return (-1);
	while (g_builtins[i].name)
	{
		if (ft_strcmp(cmd->exe->content, g_builtins[i].name) == 0
												&& g_builtins[i].func)
			return (g_builtins[i].func(cmd, shell));
		i++;
	}
	return (-1);
}
