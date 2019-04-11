/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_word_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:04:15 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/11 13:23:03 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_word_token(t_token *token)
{
	if (token->type == TOKEN_NAME)
		return (1);
	return (token->type == TOKEN_QUOTES || token->type == TOKEN_DQUOTES);
}
