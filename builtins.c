/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:50:29 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/26 12:26:25 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

//builtins del padre parte 2
static int	ft_builtdads_two(t_msh *mini, char **arr)
{
	int	argc;

	argc = ft_argc(arr);
	if (!ft_strncmp(arr[0], "unset\0", 6))
	{
		if (mini->pipelen == 0)
			ft_unset(mini, arr);
		array_free(arr);
		mini->returnval = 0;
		return (1);
	}
	else if (!ft_strncmp(arr[0], "pwd\0", 4))
	{
		ft_pwd(mini);
		array_free(arr);
		mini->returnval = 0;
		return (1);
	}
	else if (!ft_strncmp(arr[0], "cd\0", 3))
	{
		mini->returnval = ft_cd(mini, arr, argc);
		array_free(arr);
		return (1);
	}
	return (0);
}

//builtins del padre
int	ft_builtdads(t_msh *mini, char **arr)
{
	int	argc;

	if (mini->hasbuiltins)
		wait(NULL);
	argc = ft_argc(arr);
	if (!ft_strncmp(arr[0], "export\0", 7))
	{
		if (argc > 1)
			argc = ft_export_create(mini, arr, 1, 0);
		else
			argc = ft_export_print(mini, mini->env, 0);
		array_free(arr);
		mini->returnval = argc;
		return (1);
	}
	else if (!ft_strncmp(arr[0], "exit\0", 5))
	{
		mini->returnval = ft_exit(mini, arr);
		array_free(arr);
		return (1);
	}
	return (ft_builtdads_two(mini, arr));
}

//hijo builtins parte dos
static void	ft_builtins_two(t_msh *mini, char **arr)
{
	if (!ft_strncmp(arr[0], "pwd\0", 4))
	{
		ft_pwd(mini);
		array_free(arr);
		childexit(0, mini, "");
	}
	else if (!ft_strncmp(arr[0], "echo\0", 5))
	{
		ft_echo(arr);
		array_free(arr);
		childexit(0, mini, "");
	}
	else if (!ft_strncmp(arr[0], "cd\0", 3))
	{
		ft_cd(mini, arr, ft_argc(arr));
		array_free(arr);
		childexit(1, mini, "");
	}
	else if (!ft_strncmp(arr[0], "unset\0", 6))
	{
		ft_unset(mini, arr);
		array_free(arr);
		childexit(0, mini, "");
	}
}

//estos son los builtins que mira el hijo
void	ft_builtins(t_msh *mini, char **arr)
{
	int	argc;

	argc = ft_argc(arr);
	if (!ft_strncmp(arr[0], "env\0", 4))
	{
		array_free(arr);
		if (argc > 1)
			childexit(1, mini, "env: No options or arguments allowed!\n");
		ft_env(mini, mini->env);
	}
	else if (!ft_strncmp(arr[0], "export\0", 7))
	{
		if (argc > 1)
			argc = ft_export_create(mini, arr, 1, 0);
		else
			argc = ft_export_print(mini, mini->env, 0);
		array_free(arr);
		childexit(argc, mini, "");
	}
	else if (!ft_strncmp(arr[0], "exit\0", 5))
	{
		array_free(arr);
		childexit(0, mini, "");
	}
	ft_builtins_two(mini, arr);
}
