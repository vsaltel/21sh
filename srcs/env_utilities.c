/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:04:27 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/03 12:21:01 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		disp_free_env(t_env **env)
{
	if (!env || !*env)
		return (0);
	disp_env(*env);
	free_env(env);
	return (0);
}

void	free_env(t_env **env)
{
	t_env	*curr;
	t_env	*next;

	curr = *env;
	while (curr)
	{
		next = curr->next;
		free(curr->key);
		free(curr->value);
		free(curr);
		curr = next;
	}
	*env = NULL;
}

size_t	get_var_size(char *key)
{
	size_t	ret;

	if (!key || key[0] != '$')
		return (0);
	key++;
	ret = -1;
	while (key[++ret])
	{
		if (key[ret] == '?')
			return (1);
		if (!ft_isalnum(key[ret]) && key[ret] != '_')
			break ;
	}
	return (ret);
}

char	**dup_argv(int argc, char **args, char ***argv)
{
	char	**new;
	int		i;

	if (!(new = (char **)malloc(sizeof(char *) * (argc + 1))))
		exit(1);
	i = -1;
	while (++i < argc)
		new[i] = args[i];
	new[i] = NULL;
	free(*argv);
	*argv = new;
	return (new);
}
