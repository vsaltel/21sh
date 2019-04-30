/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:12:36 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/30 15:10:38 by frossiny         ###   ########.fr       */
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
		/*
		int i;
		i = -1;
		move_cursor(10, 10);
		while (buf[++i])
			ft_printf("%d |", buf[i]);
		*/
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

void		new_entry(char **str, char *buf, t_cursor_pos *pos
		, t_history *histo)
{
	char *l;
	char *r;

	histo->pos = 0;
	pos->compl = 0;
	if (!*str)
		*str = ft_strdup(buf);
	else if (pos->visual_mode)
	{
		visual_replace(str, buf, pos);
		return (reprint(*str, pos, pos->x_rel));
	}
	else if ((*str)[pos->x_rel])
	{
		l = ft_strndup(*str, pos->x_rel);
		r = ft_strjoin(buf, *str + pos->x_rel);
		*str = ft_strfjoin(l, r, *str);
		ft_multifree(&l, &r, NULL);
	}
	else
		*str = ft_strfjoin(*str, buf, *str);
	reprint(*str, pos, pos->x_rel + ft_strlen(buf));
}

static int	check_input(char *buf, char **str, t_cursor_pos *pos
		, t_shell *shell)
{
	if (!ft_strcmp(buf, "\004"))
	{
		free(buf);
		ft_strdel(&(shell->history.first_command));
		ft_strdel(str);
		return (0);
	}
	if (g_clear_buffer)
	{
		free(buf);
		ft_strdel(str);
		g_clear_buffer = 0;
		g_return = 1;
		final_position(pos);
		return (1);
	}
	return (2);
}

int			termcaps_gnl(int fd, char **dest, t_shell *shell)
{
	int				ret;
	char			*buf;

	if (!memset_all(&(g_pos.str), &(shell->history), &g_pos))
		return (-1);
	signal(SIGWINCH, &resize);
	while ((ret = read_all(fd, &buf)))
	{
		if (ret == -1
			|| (ret = check_input(buf, &(g_pos.str), &g_pos, shell)) <= 1)
			return (ret);
		if (buf[0] == '\n')
			break ;
		if (is_special(buf))
			execute_termcaps(buf, &(g_pos.str), &g_pos, shell);
		else
			new_entry(&(g_pos.str), buf, &g_pos, &(shell->history));
		free(buf);

		int i;
		i = -1;
		move_cursor(0, 0);
		ft_printf("x = %d, y = %d x_rel = %d\nx_lastc = %d, y_lastc = %d\nx_max = %d, y_max = %d\nvisual = %d, v_beg = %d", g_pos.x, g_pos.y, g_pos.x_rel, g_pos.x_lastc, g_pos.y_lastc, g_pos.x_max, g_pos.y_max, g_pos.visual_mode, g_pos.v_beg);
		move_cursor(g_pos.x, g_pos.y);

	}
	final_position(&g_pos);
	ft_strdel(&(shell->history.first_command));
	add_to_history(g_pos.str, &(shell->history));
	free(buf);
	*dest = g_pos.str;
	return (ret > 0 ? 1 : ret);
}

int			get_input(int fd, char **dest, t_shell *shell)
{
	int				ret;

	*dest = NULL;
	if (shell->able_termcaps)
		ret = termcaps_gnl(fd, dest, shell);
	else
		ret = get_next_line(fd, dest);
	return (ret);
}
