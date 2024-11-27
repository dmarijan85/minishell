/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpmedoctor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:59:18 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/27 17:44:46 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

static void	here_doc_put_in(char *delim, int fd)
{
	char	*ret;

	wait_signal(2);
	while (1)
	{
		ret = readline("heredoc> ");
		if (!ret || ft_strncmp(ret, delim, ft_strlen(delim) + 1) == 0)
		{
			if (!ret)
			{
				ft_printf(1, "msh: warning: here-document delimited ");
				ft_printf(1, "by end-of-file (wanted '%s')\n", delim);
			}
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
	int		terminal;

	mini->herectr++;
	pid = fork();
	if (pid == -1)
		errexit(mini, "fork error: fork returned -1!\n");
	if (!pid)
		here_doc_put_in(node->str, open_file(mini, ".heredoc", TRUNC));
	waitpid(pid, &terminal, 0);
	if (terminal)
		errexit(mini, "");
}
