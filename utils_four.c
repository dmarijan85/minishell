/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_four.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:18:12 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/27 17:56:26 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

char	*get_path(char *cmd)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

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

static void	do_it_pee(t_msh *mini, char *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		errexit(mini, "msh: fork failure!?\n");
	if (!pid)
	{
		wait_signal(0);
		exec(mini, cmd);
	}
	mini->lastpid = pid;
}

void	do_last(t_msh *mini, char *cmd)
{
	char	**arr;
	char	*tmp;

	tmp = ft_strdup(cmd);
	wait_signal(0);
	wildfinder(mini, &tmp, true);
	arr = wordsplit(mini, tmp, false);
	free(tmp);
	if (!arr || !*arr)
	{
		array_free(arr);
		return ;
	}
	if (ft_builtdads(mini, arr))
	{
		mini->lastisbuiltin = true;
		return ;
	}
	array_free(arr);
	do_it_pee(mini, cmd);
}
