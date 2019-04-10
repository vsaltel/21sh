/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 18:49:29 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/10 16:42:49 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

typedef struct	s_history
{
	char					*str;
	size_t					len;
	struct s_history		*next;
}				t_history;

typedef struct	s_history_info
{
	t_history		**history;
	size_t			history_line;
	size_t			history_size;
	char			*first_command;
}				t_history_info;

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

typedef struct	s_ex_caps
{
	const char		*content;
	size_t			size;
	void     		(*func)(char **str, t_cursor_pos *pos, t_history_info *histo);
}				t_ex_caps;

void	termcaps_up(char **str, t_cursor_pos *pos, t_history_info *histo);
void	termcaps_down(char **str, t_cursor_pos *pos, t_history_info *histo);
void	termcaps_left_word(char **str, t_cursor_pos *pos, t_history_info *histo);
void	termcaps_right_word(char **str, t_cursor_pos *pos, t_history_info *histo);
void	termcaps_left(char **str, t_cursor_pos *pos, t_history_info *histo);
void	termcaps_right(char **str, t_cursor_pos *pos, t_history_info *histo);
void	termcaps_delete(char **str, t_cursor_pos *pos, t_history_info *histo);
void	termcaps_history_next(char **str, t_cursor_pos *pos, t_history_info *histo);
void	termcaps_history_prev(char **str, t_cursor_pos *pos, t_history_info *histo);
void	termcaps_home(char **str, t_cursor_pos *pos, t_history_info *histo);
void	termcaps_end(char **str, t_cursor_pos *pos, t_history_info *histo);

static const t_ex_caps g_caps_list[] =
{
	{"\e[1;2A", 6, &termcaps_up},
	{"\e[1;2B", 6, &termcaps_down},
	{"\e[1;2C", 6, &termcaps_right_word},
	{"\e[1;2D", 6, &termcaps_left_word},
	{"\e[D", 3, &termcaps_left},
	{"\e[C", 3, &termcaps_right},
	{"\e[A", 3, &termcaps_history_next},
	{"\e[B", 3, &termcaps_history_prev},
	{"\e[H", 3, &termcaps_home},
	{"\e[F", 3, &termcaps_end},
	{"\177", 1, &termcaps_delete},
	{"\011", 1, NULL},
	{NULL, 1, NULL}
};

#endif
