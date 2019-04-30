/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:26:44 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/25 15:47:37 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ht_hash(size_t size, char *key)
{
	unsigned int	hash;
	unsigned int	g;
	register char	*p;

	hash = 0;
	p = key;
	while (*p)
	{
		hash = (hash << 4) + *p;
		if ((g = hash & 0xf0000000))
		{
			hash ^= g >> 24;
			hash ^= g;
		}
		p++;
	}
	return (hash % size);
}

static int	ht_create(t_shell *shell, size_t size)
{
	t_hashval	*htab;
	size_t		i;

	if (shell->bin_ht.table)
		return (0);
	if (!(htab = (t_hashval *)malloc(sizeof(t_hashval) * size)))
		return (0);
	shell->bin_ht.size = size;
	i = -1;
	while (++i < size)
	{
		htab[i].key = NULL;
		htab[i].value = NULL;
	}
	shell->bin_ht.table = htab;
	return (1);
}

void		ht_delete(t_shell *shell)
{
	int		i;

	if (!shell->bin_ht.table)
		return ;
	i = -1;
	while (++i < shell->bin_ht.size)
	{
		free(shell->bin_ht.table[i].key);
		free(shell->bin_ht.table[i].value);
	}
	free(shell->bin_ht.table);
}

void		ht_put(t_shell *shell, char *key, char *value)
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

char		*ht_get(t_shell *shell, char *key)
{
	int hash;

	if (!shell->bin_ht.table)
		return (NULL);
	hash = ht_hash(shell->bin_ht.size, key);
	if (shell->bin_ht.table[hash].key)
		return (ft_strdup(shell->bin_ht.table[hash].value));
	return (NULL);
}

int		ht_exists(t_shell *shell, char *key)
{
	int hash;

	if (shell->bin_ht.table == NULL)
		return (0);
	hash = ht_hash(shell->bin_ht.size, key);
	if (shell->bin_ht.table[hash].key)
		return (1);
	return (0);
}
