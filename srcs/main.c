/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:43:47 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/10 19:12:47 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		g_child;
int		g_ignore_signals;
int		g_return;
int		g_clear_buffer;

int		main(int argc, char *argv[], char *envp[])
{
	t_env		*env;
	t_history	*history;

	(void)argc;
	(void)argv;
	termcaps_init();
	g_child = 0;
	g_ignore_signals = 0;
	g_return = 0;
	register_signals();
	env = NULL;
	env = copy_env(envp, 1);
	history = NULL;
	return (minishell(&env, &history));
}
