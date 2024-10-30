/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:50:29 by dmarijan          #+#    #+#             */
/*   Updated: 2024/10/30 14:05:32 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtdads(t_msh *mini, char **arr)
{
	int	argc;

	argc = ft_argc(arr);
	if (!ft_strncmp(arr[0], "export", 6))
	{
		if (argc > 1)
			ft_export_create(mini, arr, 1);
		else
			ft_export_print(mini, mini->env);
		array_free(arr);
		return (1);
	}
	else if (!ft_strncmp(arr[0], "exit", 4))
		ft_exit(mini, arr);
	return (0);
}

void	ft_builtins(t_msh *mini, char **arr)
{
	int	argc;

	argc = ft_argc(arr);
	if (!ft_strncmp(arr[0], "env", 3))
	{
		array_free(arr);
		if (argc > 1)
			childexit(mini, "env: No options or arguments allowed!\n");
		ft_env(mini, mini->env);
	}
	else if (!ft_strncmp(arr[0], "export", 6))
	{
		if (argc > 1)
			ft_export_create(mini, arr, 1);
		else
			ft_export_print(mini, mini->env);
		array_free(arr);
		exit(0);
	}
	else if (!ft_strncmp(arr[0], "exit", 4))
		ft_exit(mini, arr);
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
		array_free(arr);
		return ;
	}
	ft_printstderr("exit\n");
	if (argc > 1)
	{
		buf = ft_atoi(arr[1]);
		array_free(arr);
		exit(buf);
	}
	array_free(arr);
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
				append_envvar(&mini->envvar, ft_substr(args[i], start, \
				finnish), NULL, mini);
				i++;
				break ;
			}
			finnish++;
		}
		if (args[i])
		{
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
