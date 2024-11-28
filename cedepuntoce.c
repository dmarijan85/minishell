/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cedepuntoce.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:58:41 by mclaver-          #+#    #+#             */
/*   Updated: 2024/11/28 13:23:59 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

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
		do_last(mini, tmp);
		free(tmp);
	}
	if (my_getenv("OLDPWD", mini->env, mini->envvar))
	{
		if (mini->oldpwd)
			tmp = ft_strjoin("export OLDPWD=", mini->oldpwd);
		else
			tmp = ft_strdup("export OLDPWD");
		do_last(mini, tmp);
		free(tmp);
	}
}

int	can_opendir(char *path)
{
	int	re;
	DIR	*dir;

	re = 1;
	dir = opendir(path);
	if (!dir)
		re = 0;
	else
		closedir(dir);
	return (re);
}

int	ft_cd(t_msh *mini, char **arr, int argc)
{
	if (argc > 2)
		ft_printf(2, "msh: cd: too many arguments\n");
	else if (argc == 1)
		ft_printf(2, "msh: cd: not relative or absolute path\n");
	else if (!can_opendir(arr[1]))
		ft_printf(2, "msh: cd: %s: No such file or directory\n", arr[1]);
	else
	{
		if (ft_nodesize(mini->list) != 1)
			return (1);
		if (mini->oldpwd)
			free(mini->oldpwd);
		mini->oldpwd = getcwd(NULL, 0);
		chdir(arr[1]);
		free(mini->pwd);
		mini->pwd = getcwd(NULL, 0);
		add_path_to_env(mini);
		return (0);
	}
	return (1);
}
