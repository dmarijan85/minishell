/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:40:21 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/07 13:46:18 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**whileloop_del_var(char **env, char **ret, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)))
		{
			ret[j] = ft_strdup(env[i]);
			if (!ret[j])
			{
				array_free(ret);
				return (NULL);
			}
			j++;
		}	
		i++;
	}
	env[i] = NULL;
	return (ret);
}

char	**del_var(char **env, char *str)
{
	char	**ret;
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	ret = malloc(sizeof(char *) * i);
	if (!ret)
		return (NULL);
	ret = whileloop_del_var(env, ret, str);
	return (ret);
}

void	ft_unset(t_msh *mini, char **arr)
{
	char	**tmp;
	int		i;

	i = 1;
	while (arr[i])
	{
		if (my_getenv(arr[i], mini->env, mini->envvar))
		{
			tmp = del_var(mini->env, arr[i]);
			array_free(mini->env);
			mini->env = tmp;
			i++;
		}
	}
}
