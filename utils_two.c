/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:53:10 by mclaver-          #+#    #+#             */
/*   Updated: 2024/11/26 17:18:47 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

int	open_file(t_msh *mini, char *file, t_openmodes mode)
{
	int			ret;
	char		*tmp;

	removequotes(&file);
	if (mode == READ)
		ret = open(file, O_RDONLY, 0777);
	if (mode == TRUNC)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (mode == APPEND)
		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (ret == -1)
	{
		tmp = ft_strjoin("msh: ", file);
		perror(tmp);
		free(tmp);
		errexit(mini, "");
	}
	return (ret);
}

static bool	my_findvar_two(char *name, t_envvar *envvar)
{
	t_envvar	*temp;

	temp = envvar;
	while (temp)
	{
		if (!ft_strncmp(name, temp->name, ft_strlen(name) + 1))
			return (true);
		temp = temp->next;
	}
	return (false);
}

bool	my_findvar(char *name, char **env, t_envvar *envvar, int i)
{
	int			j;
	char		*sub;

	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (!ft_strncmp(sub, name, ft_strlen(sub) + 1))
		{
			free(sub);
			return (true);
		}
		free(sub);
		i++;
	}
	return (my_findvar_two(name, envvar));
}

static char	*my_getenv_two(char *name, t_envvar *envvar)
{
	t_envvar	*temp;

	temp = envvar;
	while (temp)
	{
		if (!ft_strncmp(name, temp->name, ft_strlen(name) + 1))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

char	*my_getenv(char *name, char **env, t_envvar *envvar)
{
	int			i;
	int			j;
	char		*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (!ft_strncmp(sub, name, ft_strlen(sub) + 1))
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (my_getenv_two(name, envvar));
}
