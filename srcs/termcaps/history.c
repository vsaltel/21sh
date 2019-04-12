/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:47:28 by vsaltel           #+#    #+#             */
/*   Updated: 2019/04/10 20:11:05 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_history_info	memset_history(t_history **history)
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

void	add_to_history(char *str, t_history **history)
{
	t_history	*item;

	if (!history || !str || !str[0] || (*history && ft_strcmp(str, (*history)->str) == 0))
		return ;
	if (!(item = malloc(sizeof(t_history))))
		return ;
	if (!*history)
		item->next = NULL;
	else
		item->next = *history;
	item->str = ft_strdup(str);
	item->len = ft_strlen(str);
	*history = item;
}

	/*
	char	*read_history(int fd, size_t *content_len)
{
	char	buf[BUFF_SIZE];
	size_t	nb_nl;
	int		ret;
	char	*content;

	content = NULL;	
	*content_len = 0;
	nb_nl = 0;
	while ((ret = read(fd, buf, BUFF_SIZE - 1)) > 0)
	{
		buf[ret] = '\0';
		ret = -1;
		while (buf[++ret] && nb_nl < MAX_HISTORY)
			if (buf[ret] == '\n')
				nb_nl++;
		*content_len += ret;
		content = !content ? ft_strdup(buf) : ft_strfjoin(content, buf, content);
	}
	if (ret == -1)
		free(content);
	return ret == -1 ? (NULL) : (content);
}
	char	*home_path;
	char	*path;
	char	*content;
	size_t	content_len;
	int		fd;

	if (!(home_path = getenv("HOME")))
		return ;
	path = ft_strpathfile(home_path, ".21sh_history");	
	int		fd;

	if (access(path, F_OK))
	{
		if ((fd = open(path, O_CREAT)) == -1)
			return ;
		else
			close(fd);
	}
	if ((fd = open(path, O_RDONLY)))
	{
		if (access(path, X_OK))
			return ;
		content = read_history(fd, &content_len);
		close(fd);
	}
	if ((fd = open(path, O_WRONLY | O_TRUNC)))
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		write(fd, content, content_len);
		free(content);
		close(fd);
	}
	*/
