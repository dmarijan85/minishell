/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:25:37 by mclaver-          #+#    #+#             */
/*   Updated: 2024/10/11 14:18:17 by dmarijan         ###   ########.fr       */
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
			backup = temp->next;
			if (temp->token != 0)
			{
				remove_redir(temp);
				if (temp->prev && temp->prev->token == 0)
					append_redirs((&temp->prev->redir), open_file(temp->str, TRUNC), 0);
				else if (temp->next && temp->next->token == 0)
					append_redirs((&temp->next->redir), open_file(temp->str, TRUNC), 0);
				delete_node(&temp);	
			}
			temp = backup;
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
	mini.args = NULL;

	printf("Benvingut a la xiquipetxina!\n");
	minishell_loop(&mini);
	stack_free_nodes(&mini.list);
	free(mini.args);
	//readline tiene 204.000 bytes de leaks, ignoralos :sob:
}
/*	t_node	*temp;
	int		i;

	i = 0;
	temp = mini.list;
	if (temp)
	{
		while (temp->next)
		{
			ft_printf("Node STR %i: %s\n", i, temp->str);
			ft_printf("Node TKN %i: %i\n", i, temp->token);
			if (temp->redir)
				ft_printf("The node %i has REDIR\n", i);
			temp = temp->next;
			i++;
		}
		ft_printf("NODE STR %i: %s\n", i, temp->str);
		ft_printf("NODE TKN %i: %i\n", i, temp->token);
		if (temp->redir)
			ft_printf("The node %i has REDIR\n", i);
	}

	return (0);
}*/
