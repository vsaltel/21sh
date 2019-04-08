/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_word_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:04:15 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/08 15:05:15 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_word_token(t_token *token)
{
	return (token->type == TOKEN_NAME || token->type == TOKEN_QUOTES || token->type == TOKEN_DQUOTES);
}
