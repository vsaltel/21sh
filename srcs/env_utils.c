/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:27:57 by frossiny          #+#    #+#             */
/*   Updated: 2019/03/08 13:46:29 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_envl(t_env **env, char *key, char *value, int inc)
{
	t_env	*new;
	t_env	*tmp;

	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	new->key = ft_strdup(key);
	if (inc && ft_strcmp("SHLVL", key) == 0)
		new->value = ft_itoa(ft_atoi(value ? value : "") + 1);
	else if (!(new->value = ft_strdup(value ? value : "")))
		exit(1);
	new->next = NULL;
	if (*env)
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*env = new;
	return (new);
}

size_t	count_env(t_env *env)
{
	size_t	len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

t_env	*copy_env(char **envp, int inc)
{
	t_env	*env;
	char	**tmp;

	env = NULL;
	tmp = NULL;
	while (envp && *envp)
	{
		tmp = ft_strsplit(*envp, '=');
		new_envl(&env, tmp[0], tmp[1], inc);
		ft_strddel(&tmp);
		envp++;
	}
	return (env);
}

char	**build_env(t_env *env)
{
	char	**envp;
	size_t	i;

	if (!(envp = (char **)malloc(sizeof(char *) * (count_env(env) + 1))))
		exit(1);
	i = 0;
	while (env)
	{
		if (!(envp[i++] = ft_strjoint(env->key, "=", env->value)))
			exit(1);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

t_env	*get_enve(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
