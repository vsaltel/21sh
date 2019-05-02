/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 12:05:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/02 17:05:13 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		bslash_error(t_shell *shell, char **input, int ret)
{
	char	*ninput;
	char	*tmp;

	g_ignore_signals = 3;
	prompt();
	if (!(ret = get_input(0, &ninput, shell)))
	{
		if (g_ignore_signals)
		{
			write(1, "\n", 1);
			g_ignore_signals = 0;
			return (2);
		}
		return (130);
	}
	tmp = ft_strjoin(*input, (*ninput == '\\') ? ninput + 1 : ninput);
	free(*input);
	free(ninput);
	*input = tmp;
	g_ignore_signals = 0;
	return (0);
}

int		quote_error(t_shell *shell, char **input, int ret)
{
	char	*ninput;
	char	*tmp;

	g_ignore_signals = ret == -3 ? 2 : 1;
	prompt();
	if (!(ret = get_input(0, &ninput, shell)))
	{
		if (g_ignore_signals)
		{
			write(2,
			"21sh: unexpected EOF while looking for quote\n", 50);
			g_ignore_signals = 0;
			return (2);
		}
		return (130);
	}
	tmp = ft_strjoint(*input, "\n", ninput);
	free(*input);
	free(ninput);
	*input = tmp;
	g_ignore_signals = 0;
	return (0);
}

int		handle_input(t_shell *shell, char **input)
{
	int		ret;

	ret = 0;
	shell->lexer.size = 0;
	while ((ret = lex(*input, &(shell->lexer))) < 1)
	{
		destroy_lexer(&(shell->lexer));
		if (ret == -3 || ret == -2)
		{
			if ((ret = quote_error(shell, input, ret)))
				return (ret);
		}
		else if (ret == -4)
		{
			if ((ret = bslash_error(shell, input, ret)))
				return (ret);
		}
		else
			return (ret);
	}
	return (0);
}

int		eval_exec(t_shell *shell, char **input)
{
	int		ret;
	t_anode	*ast;

	ast = NULL;
	if ((ret = handle_input(shell, input)) == 0)
	{
		if (!input)
			return (1);
		ft_strdel(input);
		build_ast(shell, &ast);
		shell->ast = ast;
		shell->ast ? ret = parse(shell, shell->ast) : 0;
		destroy_lexer(&(shell->lexer));
		destroy_ast(shell);
	}
	return (ret);
}

int		shell(t_shell *shell)
{
	char	*input;

	shell->lexer.tokens = NULL;
	shell->lexer.state = ST_GENERAL;
	prompt();
	while ((get_input(0, &input, shell)) > 0)
	{
		g_return = eval_exec(shell, &input);
		prompt();
	}
	if (input)
		ft_strdel(&input);
	isatty(0) ? ft_putchar('\n') : 0;
	free_env(&(shell->env));
	ht_delete(shell);
	overwrite_history(shell->history.lst);
	free_history(&(shell->history));
	restore_shell(shell->prev_term);
	free(g_pos.v_str);
	return (g_return);
}
