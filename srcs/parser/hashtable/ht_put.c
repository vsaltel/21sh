/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 14:10:11 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/15 14:52:08 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void	ht_put(t_shell *shell, char *key, char *value)
{
	int		hash;

	if (shell->bin_ht.table == NULL)
		ht_create(shell, HT_SIZE);
	if (!shell->bin_ht.table)
		return ;
	hash = ht_hash(shell->bin_ht.size, key);
	if (shell->bin_ht.table[hash].key != NULL)
	{
		free(shell->bin_ht.table[hash].key);
		free(shell->bin_ht.table[hash].value);
		shell->bin_ht.table[hash].key = ft_strdup(key);
		shell->bin_ht.table[hash].value = ft_strdup(value);
	}
	else
	{
		shell->bin_ht.table[hash].key = ft_strdup(key);
		shell->bin_ht.table[hash].value = ft_strdup(value);
	}
}
