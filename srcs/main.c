/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:43:47 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/11 15:44:59 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		g_child;
int		g_ignore_signals;
int		g_return;

int		main(int argc, char *argv[], char *envp[])
{
	t_shell		shell;

	(void)argc;
	(void)argv;
	g_child = 0;
	g_ignore_signals = 0;
	g_return = 0;
	register_signals();
	shell.ret = 0;
	shell.env = NULL;
	shell.env = copy_env(envp, 1);
	shell.ast = NULL;
	return (minishell(&shell));
}
