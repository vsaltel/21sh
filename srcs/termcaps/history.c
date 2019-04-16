/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:47:28 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/15 17:11:37 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				memset_history(t_history *history)
{
	history->first_command = NULL;
	history->history_line = 0;
}

static t_histo_lst	*new_link(char *str)
{
	t_histo_lst			*item;

	if (!(item = malloc(sizeof(t_history))))
		return (NULL);
	item->str = str;
	item->len = ft_strlen(str);
	item->next = NULL;
	return (item);
}

void				add_to_history(char *str, t_history *history)
{
	t_histo_lst			*item;

	if (!history || !str || !str[0] || (history->lst && ft_strcmp(str, history->lst->str) == 0))
		return ;
	item = new_link(ft_strdup(str));
	if (history->lst)
		item->next = history->lst;
	history->lst = item;
	history->history_size++;
}

t_histo_lst		*read_history(int fd, size_t *history_size)
{
	t_histo_lst			*begin;
	t_histo_lst			*curr;
	int		ret;
	size_t	nb_nl;
	char	*buf;

	begin = NULL;
	curr = NULL;
	nb_nl = 0;
	*history_size = 0;
	while ((ret = get_next_line(fd, &buf)) == 1)
	{
		(*history_size)++;
		if (begin)
		{
			curr->next = new_link(buf);
			curr = curr->next;
		}
		else
		{
			begin = new_link(buf);
			curr = begin;
		}
		if (nb_nl++ >= MAX_HISTORY)
			break ;
	}
	return ret == -1 ? (NULL) : (begin);
}

t_history			get_history(void)
{
	t_history	histo;
	int			fd;
	char		*path;

	histo.lst = NULL;
	path = NULL;
	path = ft_strpathfile(getenv("HOME"), ".21sh_history");	
	if (access(path, F_OK))
		return (histo);
	if (access(path, X_OK))
		return (histo);
	if ((fd = open(path, O_RDONLY)))
	{
		histo.lst = read_history(fd, &(histo.history_size));
		close(fd);
	}
	free(path);
	return (histo);
}

void				overwrite_history(t_histo_lst *histo)
{
	t_histo_lst	*curr;
	char		*path;
	int			fd;

	if (!histo)
		return ;
	fd = 0;
	path = ft_strpathfile(getenv("HOME"), ".21sh_history");	
	if (!access(path, F_OK))
		if (access(path, X_OK))
			return ;
	if (fd != -1)
		if ((fd = open(path, O_CREAT | O_WRONLY | O_TRUNC)))
		{
			curr = histo;
			while (curr)
			{
				write(fd, curr->str, curr->len);
				write(fd, "\n", 1);
				curr = curr->next;
			}
			close(fd);
		}
	free(path);
}
