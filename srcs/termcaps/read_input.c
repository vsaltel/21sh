/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:12:36 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/11 15:22:06 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		my_putchar(int c)
{
	char x;

	x = (char)c;
	write(1, &x, 1);
	return (1);
}

static void	print_nb(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_putnbr(str[i]);
		ft_putchar('|');
		i++;
	}
	ft_putstr("---");
	ft_putstr(str);
}

static int		termcaps_init()
{
	int	ret;
	char	*term_var;
	struct termios term;

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


static int		get_pos(t_cursor_pos *pos)
{
	int i;
	int pow;
	char c;
	char buf[30];

	c = '\0';
	pos->x = 0;
	pos->y = 0;
	ft_memset(buf, '\0', 30);
	i = 0;
	write(1, "\033[6n", 4);
	while (c != 'R')
	{
		read(0, &c, 1);
		buf[i++] = c;
	}
	if (i-- < 2)
		return (1);
	pow = 1;
	while (buf[--i] != ';')
	{
		pos->x = pos->x + (buf[i] - '0') * pow;
		pow = pow * 10;
	}
	pow = 1;
	while (buf[--i] != '[')
	{
		pos->y = pos->y + (buf[i] - '0') * pow;
		pow = pow * 10;
	}
	tputs(tgoto(tgetstr("cm", NULL), --(pos->x), --(pos->y)), 1, my_putchar);
	return (0);
}

static int		memset_pos(t_cursor_pos *pos)
{
	if (get_pos(pos))
		return (0);
	pos->x_min = pos->x;
	pos->x_lastc = pos->x;
	pos->y_lastc = pos->y;
	pos->x_rel = 0;
	pos->x_max = tgetnum("co") - 1;
	pos->y_min = pos->y;
	pos->y_max = tgetnum("li");
	pos->auto_wrap = tgetflag("am");
	return (1);
}

static void		last_line(t_cursor_pos *pos, size_t len)
{
	size_t	line_sup;
	size_t	final_pos;
	int i;

	line_sup = (pos->x_lastc + 1 + len) / (pos->x_max + 1);
	if (line_sup + pos->y_lastc >= pos->y_max)
	{
		final_pos = pos->y_max - pos->y_lastc + line_sup - 1;
		tputs(tgoto(tgetstr("cm", NULL), 0, pos->y_lastc), 1, my_putchar);
		i = -1;
		while (++i < final_pos)
			tputs(tgetstr("sf", NULL), 1, my_putchar);
		//tputs(tgetstr("SF", NULL), pos->y_max - pos->y_lastc + line_sup - 1, my_putchar);
		pos->y_min -= final_pos;
		pos->y -= final_pos;
		tputs(tgoto(tgetstr("cm", NULL), pos->x, pos->y), 1, my_putchar);
		pos->y_lastc -= final_pos;
	}
}
static void		move_pos(t_cursor_pos *pos, size_t len)
{
	if (pos->x_lastc == pos->x_max || pos->x_lastc + len > pos->x_max)
	{
		pos->y_lastc += (pos->x_lastc + 1 + len) / (pos->x_max + 1);
		pos->x_lastc = ((pos->x_lastc + 1 + len) % (pos->x_max + 1)) - 1;
		if (pos->x_lastc == -1)
		{
			pos->y_lastc--;
			pos->x_lastc = pos->x_max;
		}
	}
	else
		pos->x_lastc += len;
	if (pos->x == pos->x_max || pos->x + len > pos->x_max)
	{
		pos->y += (pos->x + 1 + len) / (pos->x_max + 1);
		pos->x = ((pos->x + 1 + len) % (pos->x_max + 1)) - 1;
		if (pos->x == -1)
		{
			pos->y--;
			pos->x = pos->x_max;
		}
	}
	else
		pos->x += len;
	tputs(tgoto(tgetstr("cm", NULL), pos->x, pos->y), 1, my_putchar);
	pos->x_rel += len;
}

void	new_entry(char **str, char *buf, t_cursor_pos *pos)
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
		tputs(tgoto(tgetstr("cm", NULL), 0, pos->y_min + 1), 1, my_putchar);
		tputs(tgetstr("cd", NULL), 1, my_putchar);
	}
	tputs(tgoto(tgetstr("cm", NULL), pos->x_min, pos->y_min), 1, my_putchar);
	tputs(tgetstr("ce", NULL), 1, my_putchar);
	ft_printf("%s", *str);
	move_pos(pos, ft_strlen(buf));
}

int		read_all(int fd, char **dest)
{
	char 			buf[BUFF_SIZE];
	char			*str;
	int				ret;

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

int		get_input(int fd, char **dest)
{
	int 			ret;
	char 			*buf;
	char 			*str;
	t_cursor_pos	pos;

	str = NULL;
	termcaps_init();
	memset_pos(&pos);
	while ((ret = read_all(fd, &buf)))
	{
		if (ret == -1)
			return (ret);
		if (buf[0] == '\n')
			break ;
		if (!execute_termcaps(buf, &str, &pos))
			new_entry(&str, buf, &pos);
		//print_nb(buf);
		free(buf);
	}
	final_position(&pos);
	*dest = str;
	return (1);
}
