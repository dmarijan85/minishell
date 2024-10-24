/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:53:10 by mclaver-          #+#    #+#             */
/*   Updated: 2024/10/23 18:11:21 by dmarijan         ###   ########.fr       */
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

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

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
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(my_getenv("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
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

	arr = wordsplit(cmd);
	if (!arr || !*arr)
	{
		array_free(arr);
		return ;
	}
	if (!ft_strncmp(arr[0], "exit", 4))
		ft_exit(mini, arr);
	array_free(arr);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
		exec(mini, cmd, env);
}
