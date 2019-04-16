/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:59:12 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/16 15:57:46 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				termcaps_init(struct termios *prev_term)
{
	int				ret;
	char			*term_var;
	struct termios	term;

	tcgetattr(0, &term);
	if (prev_term)
	{
		*prev_term = term;
		if (!(term_var = getenv("TERM")))
			return (0);
		if ((ret = tgetent(NULL, term_var)) != 1)
			return (0);
	}
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_lflag &= ~(OPOST);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
	return (1);
}

void			restore_shell(struct termios prev_term)
{
	tcsetattr(0, TCSANOW, &prev_term);
}

int				memset_all(char **str, t_history *history, t_cursor_pos *pos)
{
	g_clear_buffer = 0;
	*str = NULL;
	memset_history(history);
	if (!memset_pos(pos))
		return (0);
	return (1);
}
