/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cedepuntoce.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:58:41 by mclaver-          #+#    #+#             */
/*   Updated: 2024/11/13 16:17:11 by mclaver-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//rutas absolutas Y relativas... creo que chdir ya controla bastante

void	add_path_to_env(t_msh *mini)
{
	char	*tmp;

	if (my_getenv("PWD", mini->env, mini->envvar))
	{
		if (mini->pwd)
			tmp = ft_strjoin("export PWD=", mini->pwd);
		else
			tmp = ft_strdup("export PWD");
		do_last(mini, tmp, mini->env);
		wait(NULL);
		free(tmp);
	}
	if (my_getenv("OLDPWD", mini->env, mini->envvar))
	{
		if (mini->oldpwd)
			tmp = ft_strjoin("export OLDPWD=", mini->oldpwd);
		else
			tmp = ft_strdup("export OLDPWD");
		do_last(mini, tmp, mini->env);
		wait(NULL);
		free(tmp);
	}
}

void	ft_cd(t_msh *mini, char **arr, int argc)
{
	if (argc > 2)
		errexit(mini, "cd: too many arguments\n");
	if (argc == 1)
		errexit(mini, "cd: not relative or absolute path\n");
	free(mini->oldpwd);
	mini->oldpwd = getcwd(NULL, 0);
	if (chdir(arr[1]))
		errexit(mini, "cd: No such file or directory\n");
	free(mini->pwd);
/*	if (ft_nodesize(mini->list) != 1)
	{
		array_free(arr);
		return ;
	}*/
	mini->pwd = getcwd(NULL, 0);
	add_path_to_env(mini);
}
