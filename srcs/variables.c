/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:16:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/03 18:05:46 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	handle_var(char **dst, t_env *var, char *dollar)
{
	char	*tmp;
	char	*tmp2;

	if (dollar[1] == '?')
	{
		tmp2 = ft_itoa(g_return);
		tmp = ft_strjoin(*dst, tmp2);
		free(tmp2);
	}
	else if (!var)
		return ;
	else
		tmp = ft_strjoin(*dst, var->value);
	ft_strdel(dst);
	*dst = tmp;
}

static int	get_var(char *str, char *buf, char **new, t_env *env)
{
	char	*tmp;
	size_t	vsize;

	if ((vsize = get_var_size(str)) == 0)
		return (0);
	if (!(*new))
		*new = ft_strdup(buf);
	else
	{
		if (!(tmp = ft_strjoin(*new, buf)))
			exit(1);
		free(*new);
		*new = tmp;
	}
	if (!(tmp = ft_strndup(str + 1, vsize)))
		exit(1);
	handle_var(new, get_enve(env, tmp), str);
	free(tmp);
	return (vsize);
}

static void	replace_token(t_token *dst, char *s1, char *s2)
{
	char	*tmp;

	if (s1)
	{
		if (!(tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
			return ;
		ft_strcpy(tmp, s1);
		ft_strcat(tmp, s2);
		free(s1);
	}
	else
		tmp = ft_strdup(s2);
	free(dst->content);
	dst->content = tmp;
}

static void	parse_token(t_token *token, t_env *env)
{
	char	*new;
	char	buf[BUFF_SIZE + 1];
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	buf[0] = '\0';
	new = NULL;
	while (++i < token->len && (token->content)[i])
	{
		if (token->content[i] == '$' && (!i || token->content[i - 1] != '\\'))
		{
			buf[j] = '\0';
			i += get_var(token->content + i, buf, &new, env);
			j = 0;
			buf[j] = '\0';
			continue ;
		}
		if (token->content[i] == '\\')
			i++;
		buf[j++] = token->content[i];
	}
	buf[j] = '\0';
	replace_token(token, new, buf);
}

int			replace_vars(t_token *curr, t_env *env)
{
	while (curr)
	{
		if (curr->type == TOKEN_NAME)
		{
			parse_token(curr, env);
			if (curr->type == TOKEN_NAME && curr->content[0] == '~')
				if (!(handle_home(curr, env)))
					return (0);
		}
		else
			break ;
		curr = curr->next;
	}
	return (1);
}
