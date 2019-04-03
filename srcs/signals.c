/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 10:40:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/03 12:21:01 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	catch_sigint(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	if (g_ignore_signals)
	{
		g_ignore_signals = 0;
		ioctl(0, TIOCSTI, "\4\0");
	}
	else if (!g_child)
	{
		g_return = 1;
		ft_printf("\033[1;31m$> \033[0m");
	}
}

void		register_signals(void)
{
	signal(SIGINT, catch_sigint);
	signal(SIGQUIT, SIG_IGN);
}
