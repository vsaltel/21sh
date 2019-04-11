/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:16:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/11 17:37:38 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	handle_var(char **dst, t_shell *shell, char *var_name)
{
	t_env	*var;
	char	*tmp;
	char	*tmp2;

	var = get_enve(shell->env, var_name);
	if (var_name[0] == '?')
	{
		tmp2 = ft_itoa(shell->ret);
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

static int	get_var(char *str, char *buf, char **new, t_shell *shell)
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
	handle_var(new, shell, tmp);
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

static void	parse_token(t_token *token, t_shell *shell)
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
			i += get_var(token->content + i, buf, &new, shell);
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

int			replace_vars(t_token *token, t_shell *shell)
{
	while (token && is_word_token(token))
	{
		parse_token(token, shell);
		if (token->type == TOKEN_NAME && token->content[0] == '~')
			if (!(handle_home(token, shell->env)))
				return (0);
		token = token->next;
	}
	return (1);
}
