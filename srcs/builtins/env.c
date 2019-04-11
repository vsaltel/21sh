/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:27:28 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/11 14:37:46 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

int				b_env(t_cmd *cmd, t_shell *shell)
{
	/*int		options;
	t_env	*nenv;
	char	*path;
	char	**args;*/

	//if (cmd->argc == 1)
		return (disp_env(shell->env));
	/*args = cmd->args;
	if (!parse_options(&options, --cmd->argc, ++args))
		return (1);
	nenv = dup_env(shell->env, options);
	parse_remove(&nenv, &(cmd->argc), &args);
	parse_add(&nenv, &(cmd->argc), &args);
	if (cmd->argc < 1)
		return (disp_free_env(&nenv));
	args = dup_argv(cmd->argc, args, &(cmd->args));
	path = NULL;
	if (!is_builtin(*args))
		path = get_exe(get_enve(nenv, "PATH") ? nenv : shell->env, *args, 0);
	path = path ? path : *args;
	ft_strcmp(path, "exit") == 0 ? free_env(shell->env) : 0;
	g_return = execute(cmd, &nenv, shell);
	(path != *(cmd->args) && !is_builtin(*(cmd->args))) ? ft_strdel(&path) : 0;
	free_env(&nenv);
	return (g_return);*/
}
