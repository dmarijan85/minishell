/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpmedoctor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:59:18 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/26 12:02:09 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

static void	here_doc_put_in(char *delim, int fd)
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
