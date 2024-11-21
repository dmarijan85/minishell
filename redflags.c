/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redflags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:34:29 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/21 15:32:45 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./inc/minishell.h"

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		ft_printf(1, "\n");
		rl_on_new_line();
		rl_redisplay();
		valssig = 1;
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	child_handler(int signal)
{
	if (signal == SIGINT)
		valssig = 130;
	else if (signal == SIGQUIT)
	{
		ft_printf(1, "Quit: 3\n");
		valssig = 131;
	}
}

void	wait_signal(int i)
{
	struct sigaction	sa;

	if (i)
		sa.sa_handler = &signal_handler;
	else
		sa.sa_handler = &child_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}
