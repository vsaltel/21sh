/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:12:36 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/26 15:16:15 by frossiny         ###   ########.fr       */
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

	last_line(pos, ft_strlen(buf));
	if (!*str)
		*str = ft_strdup(buf);
	else if ((*str)[pos->x_rel])
	{
		l = ft_strndup(*str, pos->x_rel);
		r = ft_strjoin(buf, *str + pos->x_rel);
		*str = ft_strfjoin(l, r, *str);
		ft_multifree(&l, &r, NULL);
	}
	else
		*str = ft_strfjoin(*str, buf, *str);
	if (pos->y_lastc > pos->y_min)
	{
		move_cursor(0, pos->y_min + 1);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
	}
	move_cursor(pos->x_min, pos->y_min);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	ft_printf("%s", *str);
	move_pos(pos, ft_strlen(buf));
	histo->pos = 0;
	pos->compl = 0;
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
		if (!memset_pos(pos))
			return (0);
		pos->x_rel = 0;
		g_clear_buffer = 0;
		shell->ret = 1;
	}
	return (1);
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
		if (ret == -1 || !(ret = check_input(buf, &(g_pos.str), &g_pos, shell)))
			return (ret);
		if (buf[0] == '\n')
			break ;
		if (!execute_termcaps(buf, &(g_pos.str), &g_pos, shell))
			new_entry(&(g_pos.str), buf, &g_pos, &(shell->history));
		free(buf);
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
	char			*buf;

	*dest = NULL;
	if (shell->able_termcaps)
		ret = termcaps_gnl(fd, dest, shell);
	else
		ret = get_next_line(fd, dest);
	return (ret);
}
