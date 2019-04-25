/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:53:12 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/25 13:43:09 by frossiny         ###   ########.fr       */
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
	restore_shell(shell->prev_term);
	destroy_lexer(&(shell->lexer));
	destroy_ast(shell);
	ht_delete(shell);
	exit(ret);
	return (ret);
}
