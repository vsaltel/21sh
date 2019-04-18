/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 18:49:29 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/18 17:34:31 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

typedef struct	s_histo_lst
{
	char				*str;
	size_t				len;
	struct s_histo_lst	*next;
}				t_histo_lst;

typedef struct	s_history
{
	t_histo_lst			*lst;
	size_t				pos;
	size_t				size;
	char				*first_command;
}				t_history;

/*
**	x; 			position x dans le shell
**	y; 			position y dans le shell
**	x_min; 		position x apres le prompt dans le shell
**	x_max; 		position x du dernier char de la ligne
**	x_lastc; 	postion x du dernier char rentre dans le shell
**	y_lastc; 	postion y du dernier char rentre dans le shell
**	x_rel; 		postion x dans la string
**	y_min; 		position y initiale de la ligne du prompt dans le shell
**	y_max; 		position y de la derniere affichable dans le shell
*/

typedef struct	s_cursor_pos
{
	char				*str;
	size_t				x;
	size_t				y;
	size_t				x_min;
	size_t				x_max;
	size_t				x_lastc;
	size_t				y_lastc;
	size_t				x_rel;
	size_t				y_min;
	size_t				y_max;
	int					compl;
	char				*o_input;
	size_t				opos;
	int					visual_mode : 1;
	char				*visual_str;
}				t_cursor_pos;

typedef struct	s_ex_caps
{
	const char			*content;
	size_t				size;
	void				(*func)();
}				t_ex_caps;

#endif
