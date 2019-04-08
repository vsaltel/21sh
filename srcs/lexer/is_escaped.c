/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 12:02:17 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/04 16:45:09 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_escaped(char *s, size_t index, int endquote)
{
	int	prev;

	prev = 0;
	if (index <= 0)
		return (0);
	if (s[index - 1] == '\\')
		prev = !is_escaped(s, index - 1, 0);
	if (s[index] == '\'' && endquote)
		return (0);
	return (prev);
}
