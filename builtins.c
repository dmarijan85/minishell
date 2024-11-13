/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:50:29 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/13 18:16:37 by mclaver-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtdads(t_msh *mini, char **arr)
{
	int	argc;

	argc = ft_argc(arr);
	if (!ft_strncmp(arr[0], "export\0", 7))
	{
		if (argc > 1)
			ft_export_create(mini, arr, 1);
		else
			ft_export_print(mini, mini->env);
		array_free(arr);//este
		return (1);
	}
	else if (!ft_strncmp(arr[0], "exit\0", 5))
		ft_exit(mini, arr);
	else if (!ft_strncmp(arr[0], "unset\0", 6))
	{
		ft_unset(mini, arr);
		array_free(arr);
		return (1);
	}
	else if (!ft_strncmp(arr[0], "pwd\0", 4))
	{
		ft_pwd(mini);
		array_free(arr);
		return (1);
	}
	else if (!ft_strncmp(arr[0], "cd\0", 3))
	{
		ft_cd(mini, arr, argc);
		array_free(arr);
		return (1);
	}
	return (0);
}

void	ft_builtins(t_msh *mini, char **arr)
{
	int	argc;

	argc = ft_argc(arr);
	if (!ft_strncmp(arr[0], "env\0", 4))
	{
		array_free(arr);
		if (argc > 1)
			childexit(mini, "env: No options or arguments allowed!\n");
		ft_env(mini, mini->env);
	}
	else if (!ft_strncmp(arr[0], "export\0", 7))
	{
		if (argc > 1)
			ft_export_create(mini, arr, 1);
		else
			ft_export_print(mini, mini->env);
		array_free(arr);
		childexit(mini, "");
	}
	else if (!ft_strncmp(arr[0], "exit\0", 5))
		ft_exit(mini, arr);
	else if (!ft_strncmp(arr[0], "pwd\0", 4))
	{
		ft_pwd(mini);
		array_free(arr);
		childexit(mini, "");
	}
	else if (!ft_strncmp(arr[0], "echo\0", 5))
	{
		ft_echo(arr);
		array_free(arr);
		childexit(mini, "");
	}
	else if (!ft_strncmp(arr[0], "cd\0", 3))
	{	
		array_free(arr);
		childexit(mini, "");
	}
}

void	ft_exit(t_msh *mini, char **arr)
{
	int				argc;
	unsigned char	buf;

	argc = ft_argc(arr);
	if (argc > 2)
		errexit(mini, "exit: too many arguments\n");
	if (ft_nodesize(mini->list) != 1)
	{
		array_free(arr);//este free es un problema
		return ;
	}
	ft_printstderr("exit\n");
	if (argc > 1)
	{
		buf = ft_atoi(arr[1]);
		array_free(arr);
		exit(buf);
	}
	array_free(arr);//este puede que tambien
	reset_msh(mini);
	array_free(mini->env);
	if (mini->envvar)
		stack_free_envvars(mini);
	exit(0);
}

void	ft_env(t_msh *mini, char **envp)
{
	int			i;
	t_envvar	*tmp;

	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
	tmp = mini->envvar;
	while (tmp)
	{
		if (tmp->hasvalue)
			ft_printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	childexit(mini, "");
}

void	ft_export_create(t_msh *mini, char **args, int i)
{
	char 	*tmp;
	char	*tmptwo;
	int		start;
	int		finnish;

	while (args[i])
	{
		start = 0;
		finnish = 0;
		while (args[i][finnish] != '=')
		{
			if (!(args[i][finnish]))
			{	
				tmp = ft_substr(args[i], start, finnish);
				if (!my_getenv(tmp, mini->env, mini->envvar))
				{
					if (!ft_strncmp(tmp,"PWD\0", 4))
						append_envvar(&mini->envvar, tmp, mini->pwd, mini);
					else if (!ft_strncmp(tmp, "OLDPWD\0", 7))
						append_envvar(&mini->envvar, tmp, mini->oldpwd, mini);
					else
						append_envvar(&mini->envvar, tmp, NULL, mini);
				}
				else
					free(tmp);
				i++;
				break ;
			}
			finnish++;
		}
		if (args[i])
		{
			tmp = ft_substr(args[i], start, finnish);
			if (my_getenv(tmp, mini->env, mini->envvar))
			{
				tmptwo = ft_strjoin("unset ", tmp);
				do_last(mini, tmptwo, mini->env);
				free(tmptwo);
				wait(NULL);
			}
			free(tmp);
			append_envvar(&mini->envvar, ft_substr(args[i], start, finnish), \
			ft_substr(args[i], finnish + 1, ft_strlen(args[i])), mini);
			i++;
		}
	}
}

void	ft_export_print(t_msh *mini, char **envp)
{
	int			i;
	t_envvar	*tmp;
	int			j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		ft_printf("declare -x ");
		while (envp[i][j] && envp[i][j] != '=')
			ft_printf("%c", envp[i][j++]);
		ft_printf("=\"");
		while (envp[i][j++])
			ft_printf("%c", envp[i][j]);
		ft_printf("\"\n");
		i++;
	}
	tmp = mini->envvar;
	while (tmp)
	{
		ft_printf("declare -x %s", tmp->name);
		if (tmp->hasvalue)
			ft_printf("=\"%s\"", tmp->value);
		ft_printf("\n");
		tmp = tmp->next;	
	}
}

void	ft_pwd(t_msh *mini)
{
	ft_printf("%s\n", mini->pwd);
}

void	ft_echo(char **arr)
{
	int	j;
	int	i;

	i = 1;
	j = 0;
	if (arr[i] && !ft_strncmp(arr[i], "-n", 2))
		i++;
	while (arr[i])
	{
		while (j < (int)ft_strlen(arr[i]) && arr[i][j])
		{
			ft_printf("%c", arr[i][j]);
			j++;
		}
		if (arr[i + 1])
			ft_printf(" ");
		j = 0;
		i++;
	}
	if (!arr[1] || ft_strncmp(arr[1], "-n", 2))
		ft_printf("\n");
}
