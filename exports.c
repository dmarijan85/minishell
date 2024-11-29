/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exports.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:08:25 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/29 12:21:18 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

static void	second_if(t_msh *mini, char *tmp)
{
	if (!ft_strncmp(tmp, "PWD\0", 4))
		append_envvar(&mini->envvar, tmp, mini->pwd, mini);
	else if (!ft_strncmp(tmp, "OLDPWD\0", 7))
		append_envvar(&mini->envvar, tmp, mini->oldpwd, mini);
	else
		append_envvar(&mini->envvar, tmp, NULL, mini);
}

static int	first_if(char **tmp, char *arg)
{
	ft_printf(2, "msh: export: \'%s\': not a valid identifier\n", arg);
	free(*tmp);
	*tmp = NULL;
	return (1);
}

static void	third_if(t_msh *mini, char *name, char *arg, int i)
{
	char	*tmp;
	char	*newname;
	char	*sub;
	char	*tmptwo;

	sub = ft_substr(arg, i + 1, ft_strlen(arg));
	if (i != 0 && arg[i - 1] == '+')
	{
		newname = ft_substr(name, 0, ft_strlen(name) - 1);
		free(name);
		name = newname;
		tmp = ft_strjoin(my_getenv(name, mini->env, mini->envvar), sub);
		free(sub);
		sub = tmp;
	}
	if (my_findvar(name, mini->env, mini->envvar, 0))
	{
		tmptwo = ft_strjoin("unset ", name);
		do_last(mini, tmptwo);
		free(tmptwo);
	}
	append_envvar(&mini->envvar, name, sub, mini);
}

int	ft_export_create(t_msh *mini, char **args, int i, int ret)
{
	char		*tmp;
	int			start;
	int			finnish;

	while (args[i])
	{
		start = 0;
		finnish = 0;
		while (args[i][finnish] && args[i][finnish] != '=')
			finnish++;
		tmp = ft_substr(args[i], start, finnish);
		if (!isvalid(args[i]))
			ret = first_if(&tmp, args[i]);
		else if (!args[i][finnish] && !my_findvar(tmp, mini->env, \
				mini->envvar, 0))
			second_if(mini, tmp);
		else if (args[i][finnish] == '=')
			third_if(mini, tmp, args[i], finnish);
		else
			free(tmp);
		i++;
	}
	return (ret);
}

int	ft_export_print(t_msh *mini, char **envp, int i)
{
	t_envvar	*tmp;
	int			j;

	while (envp[i])
	{
		j = 0;
		ft_printf(1, "declare -x ");
		while (envp[i][j] && envp[i][j] != '=')
			ft_printf(1, "%c", envp[i][j++]);
		ft_printf(1, "=\"");
		while (envp[i][j++])
			ft_printf(1, "%c", envp[i][j]);
		ft_printf(1, "\"\n");
		i++;
	}
	tmp = mini->envvar;
	while (tmp)
	{
		ft_printf(1, "declare -x %s", tmp->name);
		if (tmp->hasvalue)
			ft_printf(1, "=\"%s\"", tmp->value);
		ft_printf(1, "\n");
		tmp = tmp->next;
	}
	return (0);
}
