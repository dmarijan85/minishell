/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomboclaat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:52:14 by mclaver-          #+#    #+#             */
/*   Updated: 2024/10/21 12:18:02 by mclaver-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_msh *mini, char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	if (cmd && !*cmd)
		errexit(mini, "command not found: ''\n");
	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("msh: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		array_free(s_cmd);
		errexit(mini, "");
	}
}

void	here_doc_put_in(char **av, int *p_fd)
{
	char	*ret;

	close(p_fd[0]);
	while (1)
	{
		ret = readline("heredoc> ");
		if (ft_strncmp(ret, av[2], ft_strlen(av[2])) == 0)
		{
			free(ret);
			exit(0);
		}
		ft_putstr_fd(ret, p_fd[1]);
		free(ret);
	}
}

void	here_doc(char **av, t_msh *mini)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		errexit(mini, "pipe error: illegal fd assignment\n");
	pid = fork();
	if (pid == -1)
		errexit(mini, "fork error: fork returned -1!\n");
	if (!pid)
		here_doc_put_in(av, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		wait(NULL);
	}
}

void	do_pipe(t_msh *mini, char *cmd, char **env)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		errexit(mini, "pipe error: illegal fd assignment\n");
	pid = fork();
	if (pid == -1)
		errexit(mini, "fork error: fork returned -1!\n");
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		close(p_fd[1]);
		exec(mini, cmd, env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
	}
}

void	leminibomber(t_node *temp, t_msh *mini)
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
			do_last(mini, temp->str, mini->env);
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

	temp = mini->list;
	tmp0 = dup(0);
	tmp1 = dup(1);
	leminibomber(temp, mini);
	dup2(tmp0, 0);
	close(tmp0);
	dup2(tmp1, 1);
	close(tmp1);
	while ((mini->pipelen)-- >= 0)
		wait(NULL);
}
