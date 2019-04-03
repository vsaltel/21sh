/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 12:40:21 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/03 12:21:29 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h"

typedef struct	s_builtin
{
	char	*name;
	int		(*func)(int argc, char ***argv, t_env **env, t_lexer *lexer);
}				t_builtin;

const t_builtin g_builtins[] =
{
	{ "echo", &b_echo },
	{ "cd", &b_cd },
	{ "setenv", &b_setenv },
	{ "unsetenv", &b_unsetenv },
	{ "env", &b_env },
	{ "exit", &b_exit },
	{ NULL, NULL }
};

#endif
