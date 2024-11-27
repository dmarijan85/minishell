/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redflags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:34:29 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/27 17:38:42 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

int	ft_get_stt(bool flag, int val)
{
	static int	var;

	if (flag)
		var = val;
	return (var);
}

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		ft_printf(1, "\n");
		rl_on_new_line();
		rl_redisplay();
		ft_get_stt(1, 1);
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	doc_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf(1, "\n");
		ft_get_stt(true, 130);
		exit(130);
	}
}

static void	child_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_get_stt(true, 130);
		ft_printf(1, "\n");
	}
	else if (signal == SIGQUIT)
	{
		ft_printf(1, "Quit (Core Dumped)\n");
		ft_get_stt(true, 131);
	}
}

void	wait_signal(int flag)
{
	struct sigaction	sa;

	if (flag == 1)
		sa.sa_handler = &signal_handler;
	else if (flag == 0)
		sa.sa_handler = &child_handler;
	else
		sa.sa_handler = &doc_handler;
	sa.sa_flags = SA_RESTART;
	if (flag != -1)
	{
		sigaction(SIGINT, &sa, NULL);
		if (flag == 1 || flag == 2)
			signal(SIGQUIT, SIG_IGN);
		else
			sigaction(SIGQUIT, &sa, NULL);
		sigaction(SIGTERM, &sa, NULL);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
	}
}
