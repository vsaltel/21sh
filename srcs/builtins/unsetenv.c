/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:29:33 by frossiny          #+#    #+#             */
/*   Updated: 2019/03/14 12:40:07 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_link(t_env *link)
{
	free(link->key);
	free(link->value);
	free(link);
}

int			delete_env(t_env **env, char *key)
{
	t_env *prev;
	t_env *current;
	t_env *next;

	current = *env;
	if (!current)
		return (1);
	prev = NULL;
	while (current && ft_strcmp(current->key, key))
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return (0);
	next = current->next;
	free_link(current);
	if (prev)
		prev->next = next;
	else
		*env = next;
	return (1);
}

int			b_unsetenv(int argc, char ***argv, t_env **env, t_lexer *lexer)
{
	int		i;

	(void)lexer;
	if (argc < 2)
	{
		write(2, "setenv: Too few arguments.\n", 27);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (!(*argv)[i])
			break ;
		delete_env(env, (*argv)[i++]);
	}
	return (0);
}
