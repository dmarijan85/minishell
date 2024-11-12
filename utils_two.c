/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:53:10 by mclaver-          #+#    #+#             */
/*   Updated: 2024/11/12 12:40:50 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*my_getenv(char *name, char **env, t_envvar *envvar)
{
	int			i;
	int			j;
	char		*sub;
	t_envvar	*temp;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, ft_strlen(sub)) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	temp = envvar;
	while (temp)
	{
		if (!ft_strncmp(name, temp->name, ft_strlen(name) + 1))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

char	*get_path(t_msh *mini, char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	mini = mini;//TODO
	env = env;//TODO
	i = -1;
	allpath = ft_split(getenv("PATH"), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath && allpath[++i] && s_cmd)
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			array_free(allpath);
			array_free(s_cmd);
			return (exec);
		}
		free(exec);
	}
	array_free(allpath);
	array_free(s_cmd);
	return (cmd);
}

void	do_last(t_msh *mini, char *cmd, char **env)
{
	pid_t	pid;
	char	**arr;

	env = env;//TODO
	arr = wordsplit(mini, cmd, false);
	if (!arr || !*arr)
	{
		array_free(arr);
		return ;
	}
	if (ft_builtdads(mini, arr))
		return ;
	array_free(arr);
	pid = fork();
	if (pid == -1)
		errexit(mini, "msh: fork failure!?\n");
	if (!pid)
		exec(mini, cmd);
}
