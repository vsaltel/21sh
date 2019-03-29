/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 18:49:29 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/29 15:53:25 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

typedef struct	s_cursor_pos
{
	size_t			x; //position x dans le shell
	size_t			y; //position y dans le shell
	size_t			x_min; //position x apres le prompt dans le shell
	size_t			x_max; //position x du dernier char de la ligne
	size_t			x_lastc; //postion x du dernier char rentre dans le shell
	size_t			y_lastc; //postion y du dernier char rentre dans le shell
	size_t			x_rel; //postion x dans la string
	size_t			y_min; //position y initiale de la ligne du prompt dans le shell
	size_t			y_max; //position y de la derniere affichable dans le shell
}				t_cursor_pos;

typedef enum	e_caps_type
{
	CAPS_NULL,
	CAPS_DELETE,
	CAPS_LEFT,
	CAPS_RIGHT
}				t_caps_type;

typedef struct	s_ex_caps
{
	const char		*content;
	size_t			size;
	t_caps_type		type;
	int     		(*func)(char **str, t_cursor_pos *pos);
}				t_ex_caps;

int		termcaps_left(char **str, t_cursor_pos *pos);
int		termcaps_right(char **str, t_cursor_pos *pos);
int		termcaps_delete(char **str, t_cursor_pos *pos);

static const t_ex_caps g_caps_list[] =
{
	{"\e[D", 3, CAPS_LEFT, &termcaps_left},
	{"\e[C", 3, CAPS_RIGHT, &termcaps_right},
	{"\e[A", 3, CAPS_NULL, NULL},
	{"\e[B", 3, CAPS_NULL, NULL},
	{"\177", 1, CAPS_DELETE, &termcaps_delete},
	{NULL, 1, CAPS_NULL, NULL}
};

//tgetnum("co");
//tgetnum("li");
//tgetflag("os");
//tputs(tgetstr("cl", NULL), 1, ft_putchar);

//co = nb colomn
//li = nb line
//AF = define color text
//AB = define color background text
//md = grass text
//cm = replace cursor
//cl = clean text
//me = delete all set
//os = over strike

#endif
