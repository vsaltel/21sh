/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:54:50 by frossiny          #+#    #+#             */
/*   Updated: 2019/03/06 16:34:55 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inexistant(char *name)
{
	write(2, "minishell: no such file or directory: ", 38);
	write(2, name, ft_strlen(name));
	ft_putchar('\n');
}

void	not_found(char *name)
{
	write(2, "minishell: command not found: ", 30);
	write(2, name, ft_strlen(name));
	ft_putchar('\n');
}

void	permission_denied(char *name)
{
	write(2, "minishell: permission denied: ", 30);
	write(2, name, ft_strlen(name));
	ft_putchar('\n');
}

void	no_user(char *name)
{
	write(2, "minishell: no such user or named directory: ", 44);
	write(2, name, ft_strlen(name));
	ft_putchar('\n');
}
