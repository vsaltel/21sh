/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:12:36 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/16 11:54:22 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	read_all(int fd, char **dest)
{
	char	buf[BUFF_SIZE];
	char	*str;
	int		ret;

	str = NULL;
	while ((ret = read(fd, buf, BUFF_SIZE - 1)))
	{
		if (ret == -1)
			break ;
		buf[ret] = '\0';
		if (!str)
			str = ft_strdup(buf);
		else
			str = ft_strfjoin(str, buf, str);
		if (ret < BUFF_SIZE - 1)
			break ;
	}
	*dest = str;
	return (ret);
}

static void	last_line(t_cursor_pos *pos, size_t len)
{
	size_t	line_sup;
	size_t	final_pos;
	size_t	i;

	line_sup = (pos->x_lastc + 1 + len) / (pos->x_max + 1);
	if (line_sup + pos->y_lastc >= pos->y_max)
	{
		final_pos = pos->y_max - pos->y_lastc + line_sup - 1;
		tputs(tgoto(tgetstr("cm", NULL), 0, pos->y_lastc), 1, ft_putchar);
		i = -1;
		while (++i < final_pos)
			tputs(tgetstr("sf", NULL), 1, ft_putchar);
/*
**		tputs(tgetstr("SF", NULL)
**			, pos->y_max - pos->y_lastc + line_sup - 1, ft_putchar);
*/
		pos->y_min -= final_pos;
		pos->y -= final_pos;
		tputs(tgoto(tgetstr("cm", NULL), pos->x, pos->y), 1, ft_putchar);
		pos->y_lastc -= final_pos;
	}
}

void		new_entry(char **str, char *buf, t_cursor_pos *pos
		, t_history *histo)
{
	char *l;
	char *r;

	last_line(pos, ft_strlen(buf));
	if (!*str)
		*str = ft_strdup(buf);
	else if ((*str)[pos->x_rel])
	{
		l = ft_strndup(*str, pos->x_rel);
		r = ft_strjoin(buf, *str + pos->x_rel);
		*str = ft_strfjoin(l, r, *str);
	}
	else
		*str = ft_strfjoin(*str, buf, *str);
	if (pos->y_lastc > pos->y_min)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, pos->y_min + 1), 1, ft_putchar);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
	}
	tputs(tgoto(tgetstr("cm", NULL), pos->x_min, pos->y_min), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	ft_printf("%s", *str);
	move_pos(pos, ft_strlen(buf));
	histo->pos = 0;
}

static int	check_input(char *buf, char **str, t_cursor_pos *pos
		, t_shell *shell)
{
	if (!ft_strcmp(buf, "\004"))
	{
		free(shell->history.first_command);
		ft_strdel(str);
		return (0);
	}
	if (g_clear_buffer)
	{
		ft_strdel(str);
		if (!memset_pos(pos))
			return (0);
		pos->x_rel = 0;
		g_clear_buffer = 0;
		shell->ret = 1;
	}
	return (1);
}

int			get_input(int fd, char **dest, t_shell *shell)
{
	int				ret;
	char			*buf;
	char			*str;
	t_cursor_pos	pos;

	*dest = NULL;
	if (shell->able_termcaps)
	{
		if (!memset_all(&str, &(shell->history), &pos))
			return (-1);
		while ((ret = read_all(fd, &buf)))
		{
			if (ret == -1 || !(ret = check_input(buf, &str, &pos, shell)))
				return (ret);
			if (buf[0] == '\n')
				break ;
			if (!execute_termcaps(buf, &str, &pos, shell))
				new_entry(&str, buf, &pos, &(shell->history));
			free(buf);
		}
		final_position(&pos);
		free(shell->history.first_command);
		add_to_history(str, &(shell->history));
	}
	else
		ret = get_next_line(fd, &str);
	*dest = str;
	return (ret > 0 ? 1 : ret);
}
