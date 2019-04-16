/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escaped.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:24:26 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/12 14:24:47 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		lex_state_escaped(t_lexer *lexer)
{
	lexer->in++;
	lexer->state = ST_GENERAL;
	return (1);
}
