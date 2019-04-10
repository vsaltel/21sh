/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:33:56 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/10 20:35:10 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "shell.h"

typedef struct 		e_pipel
{
	t_cmd			*cmd;
	struct e_pipel	*previous;
	struct e_pipel	*next;
}					t_pipel;

int					parse(t_lexer *lexer, t_anode *ast, t_env **env);
int					execute_pipes(t_anode *node, t_env **env, t_lexer *lexer);
t_pipel				*build_pipeline(t_anode *node);


#endif