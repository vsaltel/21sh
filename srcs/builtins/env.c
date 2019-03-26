/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:27:28 by frossiny          #+#    #+#             */
/*   Updated: 2019/03/11 18:50:27 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		parse_options(int *opt, int argc, char **argv)
{
	*opt = 0;
	while (argc-- > 0)
	{
		if (ft_strcmp(*argv, "--") == 0 || (*argv)[0] != '-')
			break ;
		else if (ft_strcmp(*argv, "-u") == 0
									|| ft_strcmp(*argv, "--unset") == 0)
		{
			argc--;
			argv += 2;
			continue ;
		}
		else if ((*argv)[0] == '-' && ((*argv)[1] == '\0' || (*argv)[1] == 'i'))
			*opt |= 1;
		else if ((*argv)[0] == '-' && (*argv)[1] != '\0')
		{
			ft_putstr_fd("env: illegal option -- ", 2);
			ft_putstr_fd((*argv) + 1, 2);
			ft_putchar_fd('\n', 2);
			return (0);
		}
		argv++;
	}
	return (1);
}

static void		parse_remove(t_env **env, int *argc, char ***argv)
{
	while (*argc > 0)
	{
		if ((**argv)[0] != '-' || ft_strcmp(**argv, "--") == 0)
		{
			(*argc) -= (ft_strcmp(**argv, "--") == 0);
			(*argv) += (ft_strcmp(**argv, "--") == 0);
			break ;
		}
		if (ft_strcmp(**argv, "-u") == 0 || ft_strcmp(**argv, "--unset") == 0)
		{
			(*argv)++;
			(*argc)--;
			if (*argc > 0)
				delete_env(env, **argv);
		}
		(*argc)--;
		(*argv)++;
	}
}

static void		parse_add(t_env **env, int *ac, char ***av)
{
	char	**tmp;
	char	**argv;
	int		argc;

	argc = *ac;
	argv = *av;
	while (argc > 0)
	{
		if (!ft_strchr(*argv, '='))
			break ;
		if (!(tmp = ft_strsplit(*argv, '=')))
			exit(1);
		if ((*argv)[0] == '=' || !tmp[0])
		{
			env_invalid_arg(&argc, &argv);
			ft_strddel(&tmp);
			break ;
		}
		new_envl(env, tmp[0], tmp[1], 0);
		ft_strddel(&tmp);
		argc--;
		argv++;
	}
	*ac = argc;
	*av = argv;
}

static t_env	*dup_env(t_env *env, int option)
{
	char	**envp;
	t_env	*nenv;

	if (option)
		return (NULL);
	if (!(envp = build_env(env)))
		return (NULL);
	nenv = copy_env(envp, 0);
	ft_strddel(&envp);
	return (nenv);
}

int				b_env(int argc, char ***argv, t_env **env, t_lexer *lexer)
{
	int		options;
	t_env	*nenv;
	char	*path;
	char	**args;

	if (argc == 1)
		return (disp_env(*env));
	args = *argv;
	if (!parse_options(&options, --argc, ++args))
		return (1);
	nenv = dup_env(*env, options);
	parse_remove(&nenv, &argc, &args);
	parse_add(&nenv, &argc, &args);
	if (argc < 1)
		return (disp_free_env(&nenv));
	args = dup_argv(argc, args, argv);
	path = NULL;
	if (!is_builtin(*args))
		path = get_exe(get_enve(nenv, "PATH") ? nenv : *env, *args, 0);
	path = path ? path : *args;
	ft_strcmp(path, "exit") == 0 ? free_env(env) : 0;
	g_return = execute(path, argv, &nenv, lexer);
	(path != **argv && !is_builtin(**argv)) ? ft_strdel(&path) : 0;
	free_env(&nenv);
	return (g_return);
}
