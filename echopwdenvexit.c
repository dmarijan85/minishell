/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echopwdenvexit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:06:22 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/26 12:06:37 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	ft_pwd(t_msh *mini)
{
	ft_printf(1, "%s\n", mini->pwd);
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
			ft_printf(1, "%c", arr[i][j]);
			j++;
		}
		if (arr[i + 1])
			ft_printf(1, " ");
		j = 0;
		i++;
	}
	if (!arr[1] || ft_strncmp(arr[1], "-n", 2))
		ft_printf(1, "\n");
}

int	ft_exit(t_msh *mini, char **arr)
{
	int				argc;
	unsigned char	buf;

	argc = ft_argc(arr);
	if (argc > 2)
	{
		ft_printf(2, "msh: exit: too many arguments\n");
		return (1);
	}
	if (ft_nodesize(mini->list) != 1)
		return ((unsigned char)ft_atoi(arr[1]));
	ft_printf(2, "exit\n");
	if (argc > 1)
	{
		buf = ft_atoi(arr[1]);
		array_free(arr);
		exit(buf);
	}
	array_free(arr);
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
		ft_printf(1, "%s\n", envp[i]);
		i++;
	}
	tmp = mini->envvar;
	while (tmp)
	{
		if (tmp->hasvalue)
			ft_printf(1, "%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	childexit(0, mini, "");
}
