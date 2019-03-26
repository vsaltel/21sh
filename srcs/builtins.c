/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:03:28 by frossiny          #+#    #+#             */
/*   Updated: 2019/03/11 15:45:14 by frossiny         ###   ########.fr       */
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

int		handle_builtin(char *name, char ***argv, t_env **env, t_lexer *lex)
{
	size_t	i;
	int		argc;
	char	**tmp;

	i = 0;
	if (!name)
		return (-1);
	tmp = *argv;
	argc = 0;
	while (tmp && tmp[argc])
		argc++;
	while (g_builtins[i].name)
	{
		if (ft_strcmp(name, g_builtins[i].name) == 0 && g_builtins[i].func)
			return (g_builtins[i].func(argc, argv, env, lex));
		i++;
	}
	return (-1);
}
