/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deported.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:46:18 by dmarijan          #+#    #+#             */
/*   Updated: 2024/12/18 09:49:47 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

static int	ft_export_print_electric_bogaloo(t_msh *mini)
{
	t_envvar	*tmp;

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

int	ft_export_print(t_msh *mini, char **envp, int i)
{
	int			j;
	char		*name;
	char		*value;

	while (envp[i])
	{
		j = 0;
		ft_printf(1, "declare -x ");
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		name = ft_substr(envp[i], 0, j);
		value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]));
		ft_printf(1, "%s=\"%s\"\n", name, value);
		free(name);
		free(value);
		i++;
	}
	return (ft_export_print_electric_bogaloo(mini));
}
