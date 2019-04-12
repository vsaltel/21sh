/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:59:12 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/11 14:59:14 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				termcaps_init(void)
{
	int				ret;
	char			*term_var;
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_lflag &= ~(OPOST);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
	if (!(term_var = getenv("TERM")))
	{
		ft_printf("var TERM non trouve");
		return (-1);
	}
	if ((ret = tgetent(NULL, term_var)) != 1)
		return (-1);
	return (ret);
}

int				restore_shell(void)
{
	struct termios term;

	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, 0, &term) == -1)
		return (-1);
	return (0);
}

int				memset_all(char **str, t_history **history
		, t_history_info *histo, t_cursor_pos *pos)
{
	g_clear_buffer = 0;
	*str = NULL;
	*histo = memset_history(history);
	if (!memset_pos(pos))
		return (0);
	return (1);
}
