/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 10:40:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/22 16:16:21 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/ioctl.h>
#include "ft_printf.h"
#include "shell.h"

static void	catch_sigquit(int signal)
{
	(void)signal;
	if (g_child > 0)
		ft_printf("\n\033[1;31m[SIGNAL]\033[0m %d quit\n", g_child);
}

static void	catch_sigint(int signal)
{
	(void)signal;
	g_clear_buffer = 1;
	if (g_ignore_signals)
	{
		g_ignore_signals = 0;
		ioctl(0, TIOCSTI, "\4\0");
	}
	else if (!g_child)
	{
		g_return = 1;
		ioctl(0, TIOCSTI, "\n");
	}
}

void		register_signals(void)
{
	signal(SIGINT, catch_sigint);
	signal(SIGQUIT, catch_sigquit);
}

void		unregister_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
