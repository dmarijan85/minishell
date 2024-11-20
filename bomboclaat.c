/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomboclaat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:52:14 by mclaver-          #+#    #+#             */
/*   Updated: 2024/11/20 18:02:48 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_msh *mini, char *cmd)
{
	char	**s_cmd;
	char	*path;

	if (cmd && !*cmd)
		childexit(127, mini, "command not found: ''\n");
	wildfinder(mini, &cmd, false);
	s_cmd = wordsplit(mini, cmd, true);
	if (!s_cmd || !*s_cmd)
		childexit(1, mini, "wordsplit blew the fuck up wtf\n");
	ft_builtins(mini, s_cmd);	
	path = get_path(mini, s_cmd[0], mini->env);
	if (execve(path, s_cmd, mini->env) == -1)
	{
		ft_printf(2, "msh: command not found: %s\n", s_cmd[0]);
		array_free(s_cmd);
		childexit(127, mini, "");
	}
}

void	here_doc_put_in(char *delim, int fd)
{
	char	*ret;

	while (1)
	{
		ret = readline("heredoc> ");
		if (ft_strncmp(ret, delim, ft_strlen(delim) + 1) == 0)
		{
			free(ret);
			close(fd);
			exit(0);
		}
		ft_putstr_fd(ret, fd);
		ft_putstr_fd("\n", fd);
		free(ret);
	}
}

void	here_doc(t_msh *mini, t_node *node)
{
	pid_t	pid;

	mini->herectr++;
	pid = fork();
	if (pid == -1)
		errexit(mini, "fork error: fork returned -1!\n");
	if (!pid)
		here_doc_put_in(node->str, open_file(mini, ".heredoc", TRUNC));
	wait(NULL);
}

void	do_pipe(t_msh *mini, char *cmd, char **env)
{
	pid_t	pid;
	int		p_fd[2];

	env = env;//TODO
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

void	letxiquibomber(t_node *temp, t_msh *mini)
{
	int	i;
	int	fd_in;
	int	fd_out;

	i = mini->pipelen;
	while (i >= 0)
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
	t_node	*temp;
	int		tookthekids;

	tookthekids = 0;
	temp = mini->list;
	tmp0 = dup(0);
	tmp1 = dup(1);
	letxiquibomber(temp, mini);
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
}
