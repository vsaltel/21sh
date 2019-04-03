/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 10:50:50 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/03 12:21:01 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		get_char(char c)
{
	if (c == 'n')
		return ('\n');
	else if (c == 'r')
		return ('\r');
	else if (c == 'a')
		return ('\a');
	else if (c == 'b')
		return ('\b');
	else if (c == 'f')
		return ('\f');
	else if (c == 't')
		return ('\t');
	else if (c == 'v')
		return ('\v');
	else if (c == '\\')
		return ('\\');
	else
		return (0);
}

static void		disp(int argc, char **argv, int opt)
{
	size_t	i;

	while (argc--)
	{
		i = 0;
		while (*argv && (*argv)[i])
		{
			if ((opt & 2) && (*argv)[i] == '\\' && (*argv)[i + 1])
				ft_putchar(get_char((*argv)[++i]));
			else
				ft_putchar((*argv)[i]);
			i++;
		}
		if (argc)
			ft_putchar(' ');
		argv++;
	}
}

static int		empty_args(void)
{
	ft_putchar('\n');
	return (0);
}

int				b_echo(int argc, char ***argv, t_env **env, t_lexer *lexer)
{
	int	opt;
	int	i;

	(void)env;
	(void)lexer;
	if (argc < 2)
		return (empty_args());
	opt = 0;
	i = 0;
	while (++i < argc)
	{
		if (ft_strlen((*argv)[i]) < 2 || (*argv)[i][0] != '-')
			break ;
		if ((*argv)[i][1] == 'n')
			opt |= 1;
		else if ((*argv)[i][1] == 'e')
			opt |= 2;
		else
			break ;
	}
	disp(argc - i, (*argv) + i, opt);
	opt & 1 ? 0 : ft_putchar('\n');
	return (0);
}
