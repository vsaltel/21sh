/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:16:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/30 17:15:46 by frossiny         ###   ########.fr       */
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

static char	*find_dollar(char *str, size_t index)
{
	char *dollar;

	ft_printf("Indexxx: %ld - |%s|\n", index, str);
	dollar = ft_strchr(str + index, '$');
	ft_printf("%p: %p - %ld = %c\n", str, dollar, dollar - str, dollar ? str[dollar - str] : '\0');
	while (dollar && is_escaped(dollar, dollar - str, 0))
		dollar = ft_strchr(dollar + 1, '$');
	return (dollar);
}

static void	parse_token(t_token *token, t_shell *shell)
{
	char	*dollar;
	char	*new;
	char	*left;
	char	*key;
	char	*tmp;

	dollar = find_dollar(token->content, 0);
	while (dollar)
	{
		key = ft_strndup(dollar + 1, get_var_size(dollar));
		tmp = handle_var(shell, key);
		free(key);
		if (tmp)
		{
			left = ft_strndup(token->content, dollar - token->content);
			new = ft_strjoint(left, tmp, dollar + 1 + get_var_size(dollar));
			ft_multifree(&left, &tmp, &(token->content));
			token->content = new;
			token->len = ft_strlen(new);
			dollar = find_dollar(token->content, 0);
		}
		else
			dollar = find_dollar(token->content, (dollar - token->content) + 1);
	}
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
