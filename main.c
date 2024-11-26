/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:25:37 by mclaver-          #+#    #+#             */
/*   Updated: 2024/11/26 13:42:26 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	minishell_loop(t_msh *mini)
{
	msh_init(mini);
	mini->args = readline("msh$ ");
	if (!mini->args)
	{
		ft_printf(1, "exit\n");
		childexit(ft_get_stt(false, 0), mini, "");
	}
	shrimp_lexer(mini);
	parser(mini);
	if (mini->list)
		lebomboclaat(mini);
	if (mini->args && *(mini->args) && mini->herectr == 0)
		add_history(mini->args);
	reset_msh(mini);
	minishell_loop(mini);
}

int	main(int ac, char **av, char **envp)
{
	t_msh	mini;

	av = av;
	ft_get_stt(true, 0);
	if (ac != 1)
		ft_printf(2, "Aquest programa no tolera arguments!! >:3\n");
	else
	{
		msh_start(&mini, envp);
		do_last(&mini, "clear");
		wait(NULL);
		ft_printf(1, "\n\tT X I Q U I P E T X I N A !\n\n");
		wait_signal(true);
		minishell_loop(&mini);
	}
}
