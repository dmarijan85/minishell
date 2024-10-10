/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:25:37 by mclaver-          #+#    #+#             */
/*   Updated: 2024/10/10 15:20:35 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_msh *msh)
{
	t_node	*temp;
	t_node	*backup;

	temp = msh->list;
	backup = NULL;
	if (temp)
	{
		while (temp)
		{	
			backup = temp;
			if (temp->token != 0)
			{
				remove_redir(temp);
				if (temp->prev && temp->prev->token == 0)
					printf(" ");//append_redirs((&temp->prev->redir), open_file(temp->str, TRUNC)); //TODO: fix append redirs arg and its call to find_last_node. copy it?
				else if (temp->next && temp->next->token == 0)
					printf(" ");//append_redirs((&temp->next->redir), open_file(temp->str, TRUNC)); //TODO: fix append redirs arg and its call to find_last_node. copy it?
				temp->prev->next = temp->next; //remove current token node.
				node_free(&temp);
			}
			temp = backup;
			temp = temp->next;
		}
	}
}

void minishell_loop(t_msh *mini)
{
	mini->args = readline("testing...> ");
	lexer(mini->args, &mini->list);
	parser(mini);
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
	t_node	*temp;
	int		i;

	i = 0;
	temp = mini.list;
	if (temp)
	{
		while (temp->next)
		{
			ft_printf("Node STR %i: %s\n", i, temp->str);
			ft_printf("Node TKN %i: %i\n", i, temp->token);
			temp = temp->next;
			i++;
		}
		ft_printf("NODE STR %i: %s\n", i, temp->str);
		ft_printf("NODE TKN %i: %i\n", i, temp->token);
	}

	return (0);
}
