/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:16:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/02 13:57:02 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*handle_var(t_env *env, char *var_name)
{
	t_env	*var;

	var = get_enve(env, var_name);
	if (var_name[0] == '?')
		return (ft_itoa(g_return));
	else if (!var)
		return (NULL);
	else
		return (ft_strdup(var->value));
}

static void	fill_new(char **new, char *tmp)
{
	if (!tmp)
		return ;
	if (*new)
		*new = ft_strfjoin(*new, tmp, *new);
	else
		*new = ft_strdup(tmp);
	free(tmp);
}

static void	parse_token(t_token *token, char *str, t_env *env)
{
	char	*new;
	char	*tmp;
	size_t	li;
	size_t	i;

	i = -1;
	li = 0;
	new = NULL;
	while (str[++i])
	{
		if (!(str[i] == '$' && !is_escaped(str, i, 0)))
			continue ;
		fill_new(&new, ft_strndup(str + li, i - li));
		tmp = handle_var(env,
					ft_strndup(str + i + 1, get_var_size(str + i)));
		if (tmp)
			fill_new(&new, tmp);
		i += get_var_size(str + i);
		li = i + 1;
	}
	if (new && i > li)
		fill_new(&new, ft_strndup(str + li, i - li));
	new ? token->content = new : 0;
	new ? token->len = ft_strlen(new) : 0;
}

int			replace_vars(t_token *token, t_env *env)
{
	while (token && is_word_token(token))
	{
		parse_token(token, token->content, env);
		if (token->type == TOKEN_NAME && token->content[0] == '~')
			if (!(handle_home(token, env)))
				return (0);
		token = token->next;
	}
	return (1);
}
