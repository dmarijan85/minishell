/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomboclaat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:52:14 by mclaver-          #+#    #+#             */
/*   Updated: 2024/12/10 12:36:40 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	exec(t_msh *mini, char *cmd)
{
	char	**s_cmd;
	char	*path;

	wildfinder(mini, &cmd, false);
	s_cmd = wordsplit(mini, cmd, true);
	if (!s_cmd || !*s_cmd)
		childexit(1, mini, "");
	ft_builtins(mini, s_cmd);
	path = get_path(mini, s_cmd[0]);
	if (execve(path, s_cmd, mini->env) == -1)
	{
		ft_printf(2, "msh: command not found: '%s'\n", s_cmd[0]);
		array_free(s_cmd);
		childexit(127, mini, "");
	}
}

void	do_pipe(t_msh *mini, char *cmd, char **env)
{
	pid_t	pid;
	int		p_fd[2];

	env = env;
	wait_signal(0);
	if (pipe(p_fd) == -1)
		errexit(mini, "pipe error: illegal fd assignment\n");
	if (isbuiltin(mini, cmd))
		mini->hasbuiltins = true;
	pid = fork();
	if (pid == -1)
		errexit(mini, "fork error: fork returned -1!\n");
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		close(p_fd[1]);
		exec(mini, cmd);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
	}
}

void	letxiquibomber(t_msh *mini, int i, int fd_in, int fd_out)
{
	t_node	*temp;

	temp = mini->list;
	while (i >= 0 && temp)
	{
		fd_in = fl_redir(temp->redir, READ);
		dup2(fd_in, 0);
		if (fd_in != 0)
			close(fd_in);
		fd_out = fl_redir(temp->redir, TRUNC);
		dup2(fd_out, 1);
		if (fd_out != 1)
			close(fd_out);
		if (i > 0)
			do_pipe(mini, temp->str, mini->env);
		else if (i == 0)
			do_last(mini, temp->str);
		temp = temp->next;
		i--;
	}
	close(fd_in);
	close(fd_out);
}

void	lebomboclaat(t_msh *mini)
{
	int		tmp1;
	int		tmp0;
	int		tookthekids;

	tookthekids = 0;
	tmp0 = dup(0);
	tmp1 = dup(1);
	letxiquibomber(mini, mini->pipelen, 0, 1);
	dup2(tmp0, 0);
	close(tmp0);
	dup2(tmp1, 1);
	close(tmp1);
	waitpid(mini->lastpid, &tookthekids, 0);
	while ((mini->pipelen) > 0)
	{
		wait(NULL);
		(mini->pipelen)--;
	}
	if (!mini->lastisbuiltin && WIFEXITED(tookthekids))
		tookthekids = WEXITSTATUS(tookthekids);
	if (!mini->lastisbuiltin)
		mini->returnval = tookthekids;
	wait_signal(1);
}
