/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exports.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:08:25 by dmarijan          #+#    #+#             */
/*   Updated: 2024/12/18 09:46:46 by dmarijan         ###   ########.fr       */
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
	ft_printf(2, "msh: export: %s: not a valid identifier\n", *tmp);
	free(*tmp);
	*tmp = NULL;
	return (1);
}

static void	unset_if_alreadyfound(t_msh *mini, char *tmp, char *sub)
{
	char	*tmptwo;

	if (my_findvar(tmp, mini->env, mini->envvar, 0))
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
		else if (!args[i][finnish] && !my_findvar(tmp, mini->env, \
				mini->envvar, 0))
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
