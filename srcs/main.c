/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:43:47 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/12 17:31:24 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		g_child;
int		g_ignore_signals;
int		g_return;
int		g_clear_buffer;

int		main(int argc, char *argv[], char *envp[])
{
	t_shell		shell;

	(void)argc;
	(void)argv;
	shell.able_termcaps = termcaps_init(&(shell.prev_term));
	g_child = 0;
	g_ignore_signals = 0;
	g_return = 0;
	register_signals();
	shell.ret = 0;
	shell.env = NULL;
	shell.env = copy_env(envp, 1);
	shell.ast = NULL;
	shell.history = get_history();
	return (minishell(&shell));
}
