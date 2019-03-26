/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:53:12 by frossiny          #+#    #+#             */
/*   Updated: 2019/03/14 12:14:29 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		b_exit(int argc, char ***argv, t_env **env, t_lexer *lexer)
{
	int		ret;

	(void)env;
	if (argc > 2)
	{
		write(2, "exit: Too many arguments\n", 25);
		return (1);
	}
	ret = g_return;
	if (argc == 2)
		ret = ft_atoi((*argv)[1]);
	free(*argv);
	free_env(env);
	destroy_lexer(lexer);
	exit(ret);
	return (g_return);
}
