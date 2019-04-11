/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:33:56 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/11 17:47:24 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "shell.h"

typedef struct		s_pipel
{
	t_cmd			*cmd;
	struct s_pipel	*previous;
	struct s_pipel	*next;
}					t_pipel;

#endif
