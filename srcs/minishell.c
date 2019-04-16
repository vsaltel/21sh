/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 12:05:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/16 18:41:44 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		bslash_error(t_shell *shell, char **input, int ret)
{
	char	*ninput;
	char	*tmp;

	g_ignore_signals = 1;
	write(1, "> ", 2);
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
	return (0);
}

int		quote_error(t_shell *shell, char **input, int ret)
{
	char	*ninput;
	char	*tmp;

	g_ignore_signals = 1;
	ret ? write(1, "dquote> ", 8) : write(1, "quote> ", 7);
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
	return (0);
}

void 	disp_tokens(t_lexer *lexer)
{
	ft_printf("Size: %d - Final State: %d\n", lexer->size, lexer->state);

	t_token *cur = lexer->tokens;
	while (cur)
	{
		ft_printf("(%d = %s)\n", cur->type, cur->content);
		cur = cur->next;
	}
}

int		handle_input(t_shell *shell, char **input)
{
	int		ret;

	ret = 0;
	shell->lexer.size = 0;
	while ((ret = lex(*input, &(shell->lexer))) < 1)
	{
		destroy_lexer(&(shell->lexer));
		if ((ret == -3 || ret == -2) && (ret = quote_error(shell, input, ret)))
			return (ret);
		else if (ret == -4 && (ret = bslash_error(shell, input, ret)))
			return (ret);
		else
			return (ret);
	}
	//disp_tokens(shell->lexer);
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

int		minishell(t_shell *shell)
{
	char	*input;

	shell->lexer.tokens = NULL;
	shell->lexer.state = ST_GENERAL;
	ft_printf("\033[1;32m$> \033[0m");
	while (get_input(0, &input, shell) > 0)
	{
		eval_exec(shell, &input);
		if (shell->ret)
			ft_printf("\033[1;31m$> \033[0m");
		else
			ft_printf("\033[1;32m$> \033[0m");
	}
	if (input)
		ft_strdel(&input);
	ft_putchar('\n');
	free_env(&(shell->env));
	overwrite_history(shell->history.lst);
	free_history(&(shell->history));
	restore_shell(shell->prev_term);
	return (shell->ret);
}
