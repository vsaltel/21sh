/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:30:34 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/03 12:21:01 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			disp_env(t_env *env)
{
	if (!env)
		return (0);
	while (env)
	{
		ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

static int	is_unique_key(t_env *env, char *key, char *value)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			if (!(env->value = ft_strdup(value)))
				exit(1);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

static int	is_key_valid(char *str)
{
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

int			b_setenv(int argc, char ***argv, t_env **env, t_lexer *lexer)
{
	(void)lexer;
	if (argc == 1)
		return (disp_env(*env));
	else if (argc > 3)
	{
		write(2, "setenv: Too many arguments.\n", 28);
		return (1);
	}
	else if (!ft_isalpha((*argv)[1][0]) && (*argv)[1][0] != '_')
	{
		write(2,
		"setenv: Variable name must begin with a letter.\n", 48);
		return (2);
	}
	else if (!is_key_valid((*argv)[1]))
	{
		write(2,
		"setenv: Variable name must contain alphanumeric characters.\n", 60);
		return (3);
	}
	if (is_unique_key(*env, (*argv)[1], argc == 3 ? (*argv)[2] : ""))
		return (0);
	if (!(new_envl(env, (*argv)[1], argc > 2 ? (*argv)[2] : "", 0)))
		return (1);
	return (0);
}
