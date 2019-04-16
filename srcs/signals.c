/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 10:40:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/16 15:33:26 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	catch_sigint(int signal)
{
	(void)signal;
	g_clear_buffer = 1;
	g_child > 0 ? write(1, "\n", 1) : 0;
	if (g_ignore_signals)
	{
		g_ignore_signals = 0;
		ioctl(0, TIOCSTI, "\4\0");
	}
	else if (!g_child)
		ioctl(0, TIOCSTI, "\n");
}

void		register_signals(void)
{
	signal(SIGINT, catch_sigint);
	signal(SIGQUIT, SIG_IGN);
}
