/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:47:28 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/12 16:44:25 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_history_info		memset_history(t_history **history)
{
	t_history_info	hist;
	t_history		*curr;

	hist.first_command = NULL;
	hist.history = history;
	hist.history_line = 0;
	if (history)
	{
		hist.history_size = 0;
		curr = *history;
		while (curr)
		{
			hist.history_size++;
			curr = curr->next;
		}
	}
	return (hist);
}

static t_history	*new_link(char *str)
{
	t_history	*item;

	if (!(item = malloc(sizeof(t_history))))
		return (NULL);
	item->str = str;
	item->len = ft_strlen(str);
	item->next = NULL;
	return (item);
}

void				add_to_history(char *str, t_history **history)
{
	t_history	*item;

	if (!history || !str || !str[0] || (*history && ft_strcmp(str, (*history)->str) == 0))
		return ;
	item = new_link(ft_strdup(str));
	if (*history)
		item->next = *history;
	*history = item;
}

t_history			*read_history(int fd)
{
	t_history	*begin;
	t_history	*curr;
	int		ret;
	size_t	nb_nl;
	char	*buf;

	begin = NULL;
	curr = NULL;
	nb_nl = 0;
	while ((ret = get_next_line(fd, &buf)) == 1)
	{
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

t_history			*get_history(void)
{
	t_history	*histo;
	int			fd;
	char		*path;

	histo = NULL;
	path = NULL;
	path = ft_strpathfile(getenv("HOME"), ".21sh_history");	
	if (access(path, F_OK))
		return (NULL);
	if (access(path, X_OK))
		return (NULL);
	if ((fd = open(path, O_RDONLY)))
	{
		histo = read_history(fd);
		close(fd);
	}
	free(path);
	return fd ? (histo) : (NULL);
}

void				overwrite_history(t_history *histo)
{
	t_history	*curr;
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
				write(fd, curr->str, ft_strlen(curr->str));
				write(fd, "\n", 1);
				curr = curr->next;
			}
			close(fd);
		}
	free(path);
}
