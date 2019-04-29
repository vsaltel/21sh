/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:53:12 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/26 13:33:01 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		b_exit(t_cmd *cmd, t_shell *shell)
{
	int		ret;

	if (cmd->argc > 2)
	{
		write(2, "exit: Too many arguments\n", 25);
		return (1);
	}
	ret = shell->ret;
	if (cmd->argc == 2)
		ret = ft_atoi(cmd->args[1]);
	free_env(&(shell->env));
	overwrite_history(shell->history.lst);
	free_history(&(shell->history));
	free(g_pos.v_str);
	restore_shell(shell->prev_term);
	destroy_lexer(&(shell->lexer));
	destroy_ast(shell);
	exit(ret);
	return (ret);
}
