/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:25:37 by mclaver-          #+#    #+#             */
/*   Updated: 2024/10/09 14:17:05 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void minishell_loop(t_msh *mini)
{
	mini->args = readline("testing...> ");
	lexer(mini->args, mini->list);
//	if (*mini->list[0] == '\0')
//		return (reset_msh(mini));
//	add_history(args); (mirar man?)
//	parser(tools); logica de lista, crear argumento para execv, deal wildcards
//	prepare_executor(tools); llamar el bomboclaater
//	reset_msh(mini);
}	

int	main(int ac, char **av, char **envp)
{
	t_msh	mini;

	av = av;
	if (ac != 1)
	{
		printf("This program does not accept arguments!! >:3\n");
		exit(0);
	}
	mini.env = envp;
	mini.list = NULL;
	mini.reset = false;
	mini.herectr = 0;

	printf("Benvingut a la xiquipetxina!\n");
	minishell_loop(&mini);
	return (0);
}
