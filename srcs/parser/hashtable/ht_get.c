/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 14:10:30 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/01 14:10:43 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ht_get(t_shell *shell, char *key)
{
	int hash;

	if (!shell->bin_ht.table)
		return (NULL);
	hash = ht_hash(shell->bin_ht.size, key);
	if (shell->bin_ht.table[hash].key)
		return (ft_strdup(shell->bin_ht.table[hash].value));
	return (NULL);
}
