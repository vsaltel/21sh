/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:16:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/01 13:02:03 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*handle_var(t_shell *shell, char *var_name)
{
	t_env	*var;

	var = get_enve(shell->env, var_name);
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

static void	parse_token(t_token *token, char *str, t_shell *shell)
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
		tmp = handle_var(shell,
					ft_strndup(str + i + 1, get_var_size(str + i)));
		if (tmp)
			fill_new(&new, tmp);
		i += get_var_size(str + i);
		li = i + 1;
	}
	if (i > li)
		fill_new(&new, ft_strndup(str + li, i - li));
	new ? token->content = new : 0;
	new ? token->len = ft_strlen(new) : 0;
}

int			replace_vars(t_token *token, t_shell *shell)
{
	while (token && is_word_token(token))
	{
		parse_token(token, token->content, shell);
		if (token->type == TOKEN_NAME && token->content[0] == '~')
			if (!(handle_home(token, shell->env)))
				return (0);
		token = token->next;
	}
	return (1);
}
