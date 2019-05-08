/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:16:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/08 16:45:51 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*handle_var(t_env *env, char *var_name)
{
	char	*ret;
	t_env	*var;

	ret = NULL;
	var = get_enve(env, var_name);
	if (var_name[0] == '?')
		ret = ft_itoa(g_return);
	else if (!var)
		ret = NULL;
	else
		ret = ft_strdup(var->value);
	free(var_name);
	return (ret);
}

static void	fill_new(char **new, char *tmp, int esc)
{
	if (!tmp)
		return ;
	if (*new)
		*new = esc ? strjoin_escape(*new, tmp) : ft_strfjoin(*new, tmp, *new);
	else
		*new = esc ? strdup_escape(tmp) : ft_strdup(tmp);
	free(tmp);
}

static void	replace_token(t_token *token, char *str)
{
	free(token->content);
	token->content = str;
	token->len = ft_strlen(str);
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
		fill_new(&new, ft_strndup(str + li, i - li), 1);
		tmp = handle_var(env,
					ft_strndup(str + i + 1, get_var_size(str + i)));
		(tmp) ? fill_new(&new, tmp, 0) : 0;
		i += get_var_size(str + i);
		li = i + 1;
	}
	i > li ? fill_new(&new, ft_strndup(str + li, i - li), 1) : 0;
	replace_token(token, new);
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
