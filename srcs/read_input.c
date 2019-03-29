/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:12:36 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/29 18:33:14 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	add_char(char **str, char *buf, int x)
{
	char *l;	
	char *r;	

	l = ft_strndup(*str, x);
	r = ft_strjoin(buf, *str + x);
	*str = ft_strfjoin(l, r, *str);
	free(l);
	free(r);
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
	//tputs(tgoto(tgetstr("cm", NULL), --(pos->x), --(pos->y)), 1, my_putchar);
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
	pos->x_max = tgetnum("co");
	pos->y_min = pos->y;
	pos->y_max = tgetnum("li");
	return (1);
}

static void		move_pos(t_cursor_pos *pos)
{
	if (pos->x == pos->x_max)
	{
		pos->y++;
		pos->y_lastc++;
		pos->x = 0;
		pos->x_lastc = 0;
	}
	else
	{
		pos->x++;
		pos->x_lastc++;
	}
	pos->x_rel++;
}

int		get_input(int fd, char **dest)
{
	int 			ret;
	char 			buf[BUFF];
	char 			*str;
	t_cursor_pos	pos;

	str = NULL;
	termcaps_init();
	memset_pos(&pos);
	ft_memset(buf, '\0', BUFF);
	while ((ret = read(fd, buf, BUFF)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		if (!execute_termcaps(buf, &str, &pos))
		{
			if (buf[0] == 'p')
				ft_printf("x%d, y%d|", pos.x, pos.y);
			if (buf[0] == '\n')
				break ;
			if (!str)
				str = ft_strdup(buf);
			else if (str[pos.x_rel])
			{
				add_char(&str, buf, pos.x_rel);
				tputs(tgetstr("im", NULL), 1, my_putchar);
			}
			else
				str = ft_strfjoin(str, buf, str);
			ft_putchar(buf[0]);
			if (str[pos.x_rel])
				tputs(tgetstr("ei", NULL), 1, my_putchar);
			move_pos(&pos);
		}
	}
	ft_putchar('\n');
	*dest = str;
	return (1);
}
