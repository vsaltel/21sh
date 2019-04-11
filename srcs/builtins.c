/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:03:28 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/11 13:20:45 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

int		handle_builtin(t_cmd *cmd, t_env **env, t_lexer *lex)
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
			return (g_builtins[i].func(cmd, env, lex));
		i++;
	}
	return (-1);
}
