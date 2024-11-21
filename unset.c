/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:40:21 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/21 15:33:55 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

static char	**whileloop_del_env(char **env, char **ret, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[j])
	{
		if (ft_strncmp(env[j], str, ft_strlen(str)))
		{
			ret[i] = ft_strdup(env[j]);
			if (!ret[i])
			{
				array_free(ret);
				return (NULL);
    		}
    		i++;
		}
		j++;
	}
	ret[i] = NULL;
	return (ret);
}

char	**del_env(t_msh *mini, char **env, char *str)
{
	char	**ret;
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	ret = ft_calloc(sizeof(char *), i);
	if (!ret)
		errexit(mini, "malloc: malloc failure?!\n");
	ret = whileloop_del_env(env, ret, str);
	return (ret);
}

void	ft_unset(t_msh *mini, char **arr)
{
	char		**tmp;
	int			i;
	t_envvar	*var;

	i = 1;
	while (arr[i])
	{
		if (my_findvar(arr[i], mini->env, mini->envvar))
		{
			if (my_findvar(arr[i], mini->env, NULL))
			{
				tmp = del_env(mini, mini->env, arr[i]);
				array_free(mini->env);
				mini->env = tmp;
			}
			var = mini->envvar;
			while (var)
			{
				if (!ft_strncmp(arr[i], var->name, ft_strlen(var->name + 1)))
				{
					var = delete_envvar(&var);
					mini->envvar = find_first_envvar(var);
				}
				else
					var = var->next;
			}
		}
		i++;
	}
}
