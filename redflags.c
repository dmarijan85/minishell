/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redflags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:34:29 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/26 13:43:08 by dmarijan         ###   ########.fr       */
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

static void	child_handler(int signal)
{
	if (signal == SIGINT)
		ft_get_stt(true, 130);
	else if (signal == SIGQUIT)
	{
		ft_printf(1, "Quit: 3\n");
		ft_get_stt(true, 131);
	}
}

void	wait_signal(bool flag)
{
	struct sigaction	sa;

	if (flag)
		sa.sa_handler = &signal_handler;
	else
		sa.sa_handler = &child_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}
