/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:26:56 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/25 13:32:17 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include "shell.h"

typedef struct	s_hashval
{
	char	*key;
	char	*value;
}				t_hashval;

typedef struct	s_hashtable
{
	int			size;
	t_hashval	*table;
}				t_hashtable;

#endif
