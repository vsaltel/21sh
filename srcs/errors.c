/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:54:50 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/04 15:34:28 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	inexistant(char *name)
{
	write(2, "21sh: no such file or directory: ", 33);
	write(2, name, ft_strlen(name));
	ft_putchar('\n');
}

void	not_found(char *name)
{
	write(2, "21sh: command not found: ", 25);
	write(2, name, ft_strlen(name));
	ft_putchar('\n');
}

void	permission_denied(char *name)
{
	write(2, "21sh: permission denied: ", 25);
	write(2, name, ft_strlen(name));
	ft_putchar('\n');
}

void	no_user(char *name)
{
	write(2, "21sh: no such user or named directory: ", 39);
	write(2, name, ft_strlen(name));
	ft_putchar('\n');
}
