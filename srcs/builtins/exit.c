/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:53:12 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/02 13:16:52 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check_arg(t_cmd *cmd)
{
	if (!ft_strisdigit(cmd->args[1]))
	{
		write(2, "exit: Numeric argument required\n", 32);
		return (0);
	}
	return (1);
}

int			b_exit(t_cmd *cmd, t_shell *shell)
{
	int		ret;

	if (cmd->argc > 2)
	{
		write(2, "exit: Too many arguments\n", 25);
		return (1);
	}
	ret = g_return;
	if (cmd->argc == 2 && !check_arg(cmd))
		ret = 1;
	else if (cmd->argc == 2)
		ret = ft_atoi(cmd->args[1]);
	free_env(&(shell->env));
	overwrite_history(shell->history.lst);
	free_history(&(shell->history));
	free(g_pos.v_str);
	restore_shell(shell->prev_term);
	destroy_lexer(&(shell->lexer));
	destroy_ast(shell);
	ht_delete(shell);
	exit(ret);
	return (ret);
}
