/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exports.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:08:25 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/26 12:29:02 by dmarijan         ###   ########.fr       */
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

static int	first_if(char **tmp)
{
	ft_printf(2, "msh: export: %s: illegal var name\n", *tmp);
	free(*tmp);
	*tmp = NULL;
	return (1);
}

static void	unset_if_alreadyfound(t_msh *mini, char *tmp, char *sub)
{
	char	*tmptwo;

	if (my_findvar(tmp, mini->env, mini->envvar))
	{
		tmptwo = ft_strjoin("unset ", tmp);
		do_last(mini, tmptwo);
		free(tmptwo);
	}
	append_envvar(&mini->envvar, tmp, sub, mini);
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
		if (!isvalid(tmp))
			ret = first_if(&tmp);
		else if (!args[i][finnish] && !my_findvar(tmp, mini->env, mini->envvar))
			second_if(mini, tmp);
		else if (args[i][finnish] == '=')
			unset_if_alreadyfound(mini, tmp, \
				ft_substr(args[i], finnish + 1, ft_strlen(args[i])));
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
